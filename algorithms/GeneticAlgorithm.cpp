#include <GeneticAlgorithm.hpp>
#include <Utils.hpp>

std::vector<Solution> algorithm::GeneticAlgorithm::initalize_population(const instance::Instance& inst, const uint32_t pop_size) {
    std::vector<Solution> population;
    population.reserve(pop_size);

    std::vector<Tour> tour_population = tour_builder.build(inst, pop_size);

    std::vector<bool> backpack_population = backpack_builder.build(inst);

    for (size_t i = 0; i < pop_size; ++i) {
        Solution solution;
        solution.tour = tour_population[i];
        solution.backpack = backpack_population;
        solution.evaluate(inst);
        population.push_back(solution);
    }

    return population;
}

void algorithm::GeneticAlgorithm::run(const instance::Instance& inst, const Config& config) {
    std::vector<Solution> population = initalize_population(inst, config.pop_size);

    for (size_t gen = 0; gen < config.generations; gen++) {
        // Selection, crossover, mutation, and evaluation logic goes here
        // This is a placeholder for the actual genetic algorithm implementation
    }
}