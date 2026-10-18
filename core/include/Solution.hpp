#include "Instance.hpp"

#include <vector>
#include <cstdint>

#pragma once

struct Solution {
    std::vector<uint32_t> tour;
    std::vector<bool> backpack;
    double fitness = 0.0;

    double evaluate(const instance::Instance& inst);

    bool operator<(const Solution& other) const {
        return fitness < other.fitness;
    }

    bool operator>(const Solution& other) const {
        return fitness > other.fitness;
    }
};