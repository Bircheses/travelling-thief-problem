#include "Instance.hpp"

#include <vector>
#include <cstdint>

#pragma once

struct Solution {
    std::vector<uint32_t> tour;
    std::vector<bool> backpack;
    double fitness = 0.0;

    double evaluate(const instance::Instance& inst) {
        const size_t n = tour.size();

        double profit = 0.0;
        std::vector<double> weight_at(n, 0.0);

        for(size_t i = 0; i < n; i++) {
            if (!backpack[i]) continue;
            profit += inst.items[i].profit;
            weight_at[inst.items[i].assigned_city_id] += inst.items[i].weight;
        }

        const double v_to_weight_ratio = (inst.max_speed - inst.min_speed) / static_cast<double>(inst.capacity_of_knapsack);
        double current_weight = 0.0, time=0.0;
        
        for(size_t i = 0; i < n; i++) {
            current_weight += weight_at[tour[i]];
            const uint32_t from_city = tour[i];
            const uint32_t to_city = tour[(i + 1) % n];
            const double current_speed = inst.max_speed - v_to_weight_ratio * current_weight;
            time += inst.distance_matrix[from_city][to_city] / current_speed;
        }

        fitness = profit - time;
        return fitness;
    }
};