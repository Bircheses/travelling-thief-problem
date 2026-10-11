#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace instance{

class City 
{
public:
    City(uint32_t id, uint32_t x, uint32_t y) : id(id), x(x), y(y) {}
private:
    uint32_t id;
    uint32_t x;
    uint32_t y;
};

class Item
{
public:
    Item(uint32_t id, uint32_t profit, uint32_t weight, uint32_t assigned_city_id) : id(id), profit(profit), weight(weight), assigned_city_id(assigned_city_id) {}
private:
    uint32_t id;
    uint32_t profit;
    uint32_t weight;
    uint32_t assigned_city_id;
};

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