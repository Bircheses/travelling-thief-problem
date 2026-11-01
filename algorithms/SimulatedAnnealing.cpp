#include <SimulatedAnnealing.hpp>
#include <Utils.hpp>

#include <algorithm>
#include <functional>
#include <iostream>

algorithm::SimulatedAnnealing::SimulatedAnnealing(const Config& config, CSVWriter writer, unsigned seed)
    : config(config), writer(std::move(writer)), rng(seed)
{
    ConfigFactory factory(config, rng());
    tour_builder = factory.make_tour_builder();
    backpack_builder = factory.make_backpack_builder();
    mutation_operator = factory.make_mutation();
}

Solution algorithm::SimulatedAnnealing::make_solution(const instance::Instance& inst, Tour tour) {
    Solution solution;
    solution.tour = std::move(tour);
    solution.backpack = backpack_builder->build(inst);
    solution.evaluate(inst);
    return solution;
}

double algorithm::SimulatedAnnealing::run(const instance::Instance& inst) {
    std::uniform_real_distribution<> chance(0.0, 1.0);

    double current_temperature = initial_temperature;
    double best_fitness = std::numeric_limits<double>::max();
    uint32_t step = 1;

    while (current_temperature > final_temperature)
    {
        Solution current_solution = make_solution(inst, tour_builder->build(inst));
        double total_fitness = 0.0;
        double worst_fitness = std::numeric_limits<double>::max();
        double step_best_fitness = std::numeric_limits<double>::lowest();

        for (size_t i = 0; i < iterations_per_temperature; i++)
        {
            Tour new_tour = current_solution.tour;
            mutation_operator->mutate(new_tour);
            Solution new_solution = make_solution(inst, std::move(new_tour));

            double delta = new_solution.fitness - current_solution.fitness;
            if (delta >= 0 || chance(rng) < std::exp(delta / current_temperature)) {
                current_solution = std::move(new_solution);
            }

            if (current_solution.fitness > step_best_fitness) {
                step_best_fitness = current_solution.fitness;
            }

            if (current_solution.fitness > best_fitness) {
                best_fitness = current_solution.fitness;
            }

            if (current_solution.fitness < worst_fitness) {
                worst_fitness = current_solution.fitness;
            }

            total_fitness += current_solution.fitness;
        }

        writer.append(GenerationData(step++, step_best_fitness, total_fitness / iterations_per_temperature, worst_fitness));

        current_temperature *= cooling_rate;
    }

    writer.write();
    return best_fitness;
}
