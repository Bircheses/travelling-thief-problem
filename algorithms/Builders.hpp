#include <Instance.hpp>
#include <Utils.hpp>

#include <vector>
#include <cstdint>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>

#pragma once

class TourBuilder {
public:
    virtual ~TourBuilder() = default;
    virtual Tour build(const instance::Instance& inst) = 0;
    virtual std::vector<Tour> build(const instance::Instance& inst, uint32_t amount) = 0;
};

class BackpackBuilder {
public:
    virtual ~BackpackBuilder() = default;
    virtual std::vector<bool> build(const instance::Instance& inst) = 0;
};

class RandomTourBuilder : public TourBuilder {
private:    
    std::mt19937 rng;
public:    
    RandomTourBuilder(unsigned seed) : rng(seed) {};

    Tour build(const instance::Instance& inst) override
    {
        Tour tour(inst.dimension);
        std::iota(tour.begin(), tour.end(), 0);
        std::shuffle(tour.begin() + 1, tour.end(), rng);
        return tour;
    }
    
    std::vector<Tour> build(const instance::Instance& inst, uint32_t amount)
    {
        std::vector<Tour> tours;
        tours.reserve(amount);
        for (uint32_t i = 0; i < amount; ++i) {
            tours.push_back(build(inst));
        }
        return tours;
    }
};

class GreedyTourBuilder : public TourBuilder {
public:
    Tour build(const instance::Instance& inst) override
    {
        Tour tour(inst.dimension);
        std::vector<uint32_t> unvisited(inst.dimension);
        std::vector<bool> visited(inst.dimension, false);

        std::iota(unvisited.begin(), unvisited.end(), 0);

        uint32_t closest_city = 0;
        tour[0] = closest_city;
        visited[closest_city] = true;
        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), closest_city), unvisited.end());

        for (size_t i = 1; i < inst.dimension; i++) {
            auto nearest_city = std::min_element(unvisited.begin(), unvisited.end(), [&](uint32_t a, uint32_t b) {
                return inst.distance_matrix[closest_city][a] < inst.distance_matrix[closest_city][b];
            });

            closest_city = *nearest_city;
            tour[i] = closest_city;
            visited[closest_city] = true;

            unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), closest_city), unvisited.end());
        }

        return tour;
    }

    std::vector<Tour> build(const instance::Instance& inst, uint32_t amount) override
    {
        std::vector<Tour> tours;
        tours.reserve(amount);
        for (uint32_t i = 0; i < amount; ++i) {
            tours.push_back(build(inst));
        }
        return tours;
    }
};

class GreedyBackpackBuilder : public BackpackBuilder {
public:
    std::vector<bool> build(const instance::Instance& inst) override
    {
        std::vector<bool> backpack(inst.number_of_items, false);

        std::vector<uint32_t> backpack_order(inst.number_of_items);
        std::iota(backpack_order.begin(), backpack_order.end(), 0);

        std::sort(backpack_order.begin(), backpack_order.end(), [&](uint32_t a, uint32_t b) {
            double ratio_a = static_cast<double>(inst.items[a].profit) / static_cast<double>(inst.items[a].weight);
            double ratio_b = static_cast<double>(inst.items[b].profit) / static_cast<double>(inst.items[b].weight);
            return ratio_a > ratio_b;
        });

        uint32_t current_backpack_capacity = inst.capacity_of_knapsack;
        for (uint32_t item : backpack_order) {
            if (inst.items[item].weight <= current_backpack_capacity) {
                backpack[item] = true;
                current_backpack_capacity -= inst.items[item].weight;
            }
        }

        return backpack;
    }
};