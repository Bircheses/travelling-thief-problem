#include <GeneticAlgorithm.hpp>
#include <Utils.hpp>

#include <algorithm>
#include <iostream>

algorithm::GeneticAlgorithm::GeneticAlgorithm(const Config& config, unsigned seed)
    : config(config), rng(seed)
{
    ConfigFactory factory(config, rng());
    tour_builder = factory.make_tour_builder();
    backpack_builder = factory.make_backpack_builder();
    selection_operator = factory.make_selection();
    mutation_operator = factory.make_mutation();
    crossover_operator = factory.make_crossover();
}

Solution algorithm::GeneticAlgorithm::make_solution(const instance::Instance& inst, const Tour& tour) {
    Solution solution;
    solution.tour = tour;
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

Solution algorithm::GeneticAlgorithm::run(const instance::Instance& inst) {
    const uint32_t pop_size = config.pop_size;
    const uint32_t generations = config.generations;
    std::uniform_real_distribution<> chance(0.0, 1.0);

    std::vector<Solution> population = init_population(inst, pop_size);
    Solution best_ever = *std::max_element(population.begin(), population.end());

    std::vector<Solution> new_population;
    new_population.reserve(pop_size);

    for (size_t gen = 0; gen < generations; gen++) {
        while (new_population.size() < pop_size) {
            const Solution& parent1 = selection_operator->select(population);
            const Solution& parent2 = selection_operator->select(population);

            Tour child = chance(rng) < config.crossover_rate
                ? crossover_operator->crossover(parent1.tour, parent2.tour)
                : parent1.tour;

            if (chance(rng) < config.mutation_rate) {
                mutation_operator->mutate(child);
            }

            new_population.push_back(make_solution(inst, child));
        }

        population.swap(new_population);
        new_population.clear();

        const auto best = std::max_element(population.begin(), population.end());
        const auto worst = std::min_element(population.begin(), population.end());
        if (*best > best_ever) best_ever = *best;

        std::cout << "Generation " << gen + 1 << ": Best fitness = " << best->fitness << ", Worst fitness = " << worst->fitness << std::endl;
    }

    return best_ever;
}
