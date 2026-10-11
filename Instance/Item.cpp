#include "Item.hpp"

std::string instance::Item::to_string() const {
    return "{id=" + std::to_string(id) + ", profit: " + std::to_string(profit) + ", weight: " + std::to_string(weight) + ", city: " + std::to_string(assigned_city_id) + "}";
}