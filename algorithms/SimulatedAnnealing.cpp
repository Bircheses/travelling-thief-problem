#include <SimulatedAnnealing.hpp>
#include <Utils.hpp>

#include <algorithm>
#include <functional>
#include <iostream>

algorithm::SimulatedAnnealing::SimulatedAnnealing(const SAConfig& config, CSVWriter writer, unsigned seed)
    : config(config), writer(std::move(writer)), rng(seed)
{
    ConfigFactory factory(config, rng());
    tour_builder = factory.make_tour_builder();
    backpack_builder = factory.make_backpack_builder();
    mutation_operator = factory.make_mutation();
}

Solution algorithm::SimulatedAnnealing::make_solution(const instance::Instance& inst, const Tour tour) {
    Solution solution;
    solution.tour = std::move(tour);
    solution.backpack = backpack_builder->build(inst);
    solution.evaluate(inst);
    return solution;
}

std::vector<Solution> algorithm::SimulatedAnnealing::init_population(const instance::Instance& inst, const uint32_t pop_size) {
    std::vector<Solution> population;
    population.reserve(pop_size);

    for (const Tour& tour : tour_builder->build(inst, pop_size)) {
        population.push_back(make_solution(inst, tour));
    }

    return population;
}

double algorithm::SimulatedAnnealing::run(const instance::Instance& inst) {
    const uint32_t pop_size = config.pop_size;
    const uint32_t generations = config.generations;
    std::uniform_real_distribution<> chance(0.0, 1.0);

    std::vector<Solution> population = init_population(inst, pop_size);
    double best_fitness = std::max_element(population.begin(), population.end())->fitness;

    std::vector<Solution> new_population;
    new_population.reserve(pop_size);

    

    writer.write();
    return best_fitness;
}
