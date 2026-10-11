#pragma once

#include "City.hpp"
#include "Item.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace instance{

class Instance
{
public:
    Instance() = default;

    std::string problem_name;
    std::string knapsack_data_type;
    uint32_t dimension;
    uint32_t number_of_items;
    uint32_t capacity_of_knapsack;
    double min_speed;
    double max_speed;
    double renting_ratio;
    std::string edge_weight_type;

    std::vector<City> cities;
    std::vector<Item> items;

    void load(std::string filename);
    std::string to_string() const;
};

} // namespace instance