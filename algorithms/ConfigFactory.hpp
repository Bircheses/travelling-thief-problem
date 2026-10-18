#include <ConfigReader.hpp>
#include <Builders.hpp>
#include <Selection.hpp>
#include <Crossover.hpp>
#include <Mutation.hpp>

#include <memory>
#include <random>

#pragma once

class ConfigFactory {
    const Config& config;
    std::mt19937 rng;

public:
    ConfigFactory(const Config& config, unsigned seed) : config(config), rng(seed) {}

    std::unique_ptr<TourBuilder> make_tour_builder();
    std::unique_ptr<BackpackBuilder> make_backpack_builder();
    std::unique_ptr<Selection> make_selection();
    std::unique_ptr<Crossover> make_crossover();
    std::unique_ptr<Mutation> make_mutation();
};
