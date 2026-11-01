#include <Instance.hpp>
#include <Builders.hpp>
#include <ConfigReader.hpp>
#include <ConfigFactory.hpp>
#include <Solution.hpp>
#include <Mutation.hpp>
#include <Writer.hpp>

#include <memory>
#include <random>

#pragma once

namespace algorithm {

class SimulatedAnnealing {
private:
    double initial_temperature = 7600.0;
    double cooling_rate = 0.995;
    double final_temperature = 0.1;
    uint32_t iterations_per_temperature = 76;

    const Config& config;
    CSVWriter writer;
    std::mt19937 rng;
    std::unique_ptr<TourBuilder> tour_builder;
    std::unique_ptr<BackpackBuilder> backpack_builder;
    std::unique_ptr<Mutation> mutation_operator;

    Solution make_solution(const instance::Instance& inst, Tour tour);

public:
    SimulatedAnnealing(const Config& config, CSVWriter writer, unsigned seed);

    double run(const instance::Instance& inst);
};

}
