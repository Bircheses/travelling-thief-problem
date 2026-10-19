#include <Instance.hpp>
#include <Builders.hpp>
#include <ConfigReader.hpp>
#include <ConfigFactory.hpp>
#include <Solution.hpp>
#include <Selection.hpp>
#include <Mutation.hpp>
#include <Crossover.hpp>
#include <Writer.hpp>

#include <memory>
#include <random>

#pragma once

namespace algorithm {

class GeneticAlgorithm {
private:
    const Config& config;
    CSVWriter writer;
    std::mt19937 rng;
    std::unique_ptr<TourBuilder> tour_builder;
    std::unique_ptr<BackpackBuilder> backpack_builder;
    std::unique_ptr<Selection> selection_operator;
    std::unique_ptr<Mutation> mutation_operator;
    std::unique_ptr<Crossover> crossover_operator;

    Solution make_solution(const instance::Instance& inst, const Tour& tour);

public:
    GeneticAlgorithm(const Config& config, CSVWriter writer, unsigned seed);

    Solution run(const instance::Instance& inst);
    std::vector<Solution> init_population(const instance::Instance& inst, const uint32_t pop_size);
};

}
