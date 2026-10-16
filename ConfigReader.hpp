#pragma once

#include <string>

struct Config {
    unsigned pop_size = 100;
    unsigned generations = 10;
    double crossover_rate = 0.8;
    double mutation_rate = 0.1;
    std::string selection_method = "tournament";
    std::string tour_builder = "random";

    static Config load(const std::string& filename);
};
