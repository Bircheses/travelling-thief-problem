#include "Instance.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

std::vector<std::vector<double>> create_distance_matrix(std::vector<instance::City>& cities) {
    const size_t n = cities.size();
    std::vector<std::vector<double>> distance_matrix(n, std::vector<double>(n, 0.0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                double dx = cities[i].x - cities[j].x;
                double dy = cities[i].y - cities[j].y;
                distance_matrix[i][j] = std::ceil(std::sqrt(dx * dx + dy * dy));
            }
        }
    }

    return distance_matrix;
}

void instance::Instance::load(std::string filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    problem_name = line.substr(line.find(":") + 1);
    std::getline(file, line);
    knapsack_data_type = line.substr(line.find(":") + 1);
    std::getline(file, line);
    dimension = std::stoi(line.substr(line.find(":") + 1));
    std::getline(file, line);
    number_of_items = std::stoi(line.substr(line.find(":") + 1));
    std::getline(file, line);
    capacity_of_knapsack = std::stoi(line.substr(line.find(":") + 1));
    std::getline(file, line);
    min_speed = std::stod(line.substr(line.find(":") + 1));
    std::getline(file, line);
    max_speed = std::stod(line.substr(line.find(":") + 1));
    std::getline(file, line);
    renting_ratio = std::stod(line.substr(line.find(":") + 1));
    std::getline(file, line);
    edge_weight_type = line.substr(line.find(":") + 1);

    std::getline(file, line); // Skip the "NODE_COORD_SECTION" line

    cities.reserve(dimension);
    for (size_t i = 0; i < dimension; i++) {
        uint32_t id; 
        float x, y;
        file >> id >> x >> y;
        cities.emplace_back(id, x, y);
    }

    std::getline(file, line);
    std::getline(file, line);

    items.reserve(number_of_items);
    for (uint32_t i = 0; i < number_of_items; i++) {
        uint32_t id, profit, weight, assigned_city_id;
        file >> id >> profit >> weight >> assigned_city_id;
        items.emplace_back(id, profit, weight, assigned_city_id);
    }

    distance_matrix = create_distance_matrix(cities);
}

std::string instance::Instance::to_string() const
{
    std::string s;
    
    s += "Instance: " + problem_name + ", Knapsack Data Type: " + knapsack_data_type + ", Dimension: " + std::to_string(dimension) + ", Number of Items: " + std::to_string(number_of_items) + ", Capacity of Knapsack: " + std::to_string(capacity_of_knapsack) + ", Min Speed: " + std::to_string(min_speed) + ", Max Speed: " + std::to_string(max_speed) + ", Renting Ratio: " + std::to_string(renting_ratio) + ", Edge Weight Type: " + edge_weight_type;

    s+= "\nCities:{";
    for (const auto& city : cities) {
        s += city.to_string() + ", ";
    }

    s += "}\nItems:{";
    for (const auto& item : items) {
        s += item.to_string() + ", ";
    }
    s += "}\n";

    return s;
}