#pragma once

#include <cstdint>
#include <string>

namespace instance
{

class Item
{
private:
    uint32_t id;
    uint32_t profit;
    uint32_t weight;
    uint32_t assigned_city_id;
public:
    Item(uint32_t id, uint32_t profit, uint32_t weight, uint32_t assigned_city_id) : id(id), profit(profit), weight(weight), assigned_city_id(assigned_city_id) {}
    std::string to_string() const;
};

} // namespace instance