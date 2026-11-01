#include "Item.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <map>

#pragma once

namespace instance{

class City 
{
public:
    uint32_t id;
    float x;
    float y;
    
    City(uint32_t id, float x, float y) : id(id), x(x), y(y) {}
    std::string to_string() const;
};

} // namespace instance