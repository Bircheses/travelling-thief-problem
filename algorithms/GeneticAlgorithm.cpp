#include <GeneticAlgorithm.hpp>
#include <Utils.hpp>

#include <algorithm>
#include <functional>
#include <iostream>

algorithm::GeneticAlgorithm::GeneticAlgorithm(const Config& config, CSVWriter writer, unsigned seed)
    : config(config), writer(std::move(writer)), rng(seed)
{
    ConfigFactory factory(config, rng());
    tour_builder = factory.make_tour_builder();
    backpack_builder = factory.make_backpack_builder();
    selection_operator = factory.make_selection();
    mutation_operator = factory.make_mutation();
    crossover_operator = factory.make_crossover();
}

Solution algorithm::GeneticAlgorithm::make_solution(const instance::Instance& inst, const Tour tour) {
    Solution solution;
    solution.tour = std::move(tour);
    solution.backpack = backpack_builder->build(inst);
    solution.evaluate(inst);
    return solution;
}

std::vector<Solution> algorithm::GeneticAlgorithm::init_population(const instance::Instance& inst, const uint32_t pop_size) {
    std::vector<Solution> population;
    population.reserve(pop_size);

    for (const Tour& tour : tour_builder->build(inst, pop_size)) {
        population.push_back(make_solution(inst, tour));
    }

    return population;
}

double algorithm::GeneticAlgorithm::run(const instance::Instance& inst) {
    const uint32_t pop_size = config.pop_size;
    const uint32_t generations = config.generations;
    std::uniform_real_distribution<> chance(0.0, 1.0);

    std::vector<Solution> population = init_population(inst, pop_size);
    double best_fitness = std::max_element(population.begin(), population.end())->fitness;
    uint32_t stagnation_counter = 0;
    std::vector<Solution> new_population;
    new_population.reserve(pop_size);

    for (size_t gen = 0; gen < generations; gen++) {
        if (config.elitarism) {
            size_t elite_size = config.elite_size;
            std::partial_sort(population.begin(), population.begin() + elite_size, population.end(), std::greater<>{});
            new_population.insert(new_population.end(), population.begin(), population.begin() + elite_size);
        }

        while (new_population.size() < pop_size) {
            const Solution& parent1 = selection_operator->select(population);
            const Solution& parent2 = selection_operator->select(population);

            const bool crossed = chance(rng) < config.crossover_rate;
            const bool mutated = chance(rng) < config.mutation_rate;

            if (!crossed && !mutated) {
                new_population.push_back(parent1);
                continue;
            }

            Tour child = parent1.tour;

            if (crossed)
            {
                child = crossover_operator->crossover(parent1.tour, parent2.tour);
            }

            if (mutated)
            {
                mutation_operator->mutate(child);
            }

            new_population.push_back(make_solution(inst, std::move(child)));
        }

        population.swap(new_population);
        new_population.clear();

        GenerationData gen_data(gen + 1, population);
        writer.append(gen_data);

        if (!config.stagnation) stagnation_counter = 0;

        if (gen_data.best > best_fitness) {
            best_fitness = gen_data.best;
            stagnation_counter = 0;
        } else if (config.max_stagnation > 0 && ++stagnation_counter >= config.max_stagnation) {
            break;
        }  
    }

    writer.write();
    return best_fitness;
}
