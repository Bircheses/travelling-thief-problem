#include "Instance.hpp"
#include "Builders.hpp"
#include "ConfigReader.hpp"
#include "Solution.hpp"

#pragma once

namespace algorithm {

class GeneticAlgorithm {
    TourBuilder& tour_builder;
    BackpackBuilder& backpack_builder;

public:
    GeneticAlgorithm(TourBuilder& tour_builder, BackpackBuilder& backpack_builder)
        : tour_builder(tour_builder), backpack_builder(backpack_builder) {}
    void run(const instance::Instance& instance, const Config& config);
    std::vector<Solution> initalize_population(const instance::Instance& instance, const uint32_t pop_size);
};

}