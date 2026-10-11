#pragma once

#include <cstdint>
#include <string>

namespace instance{

class City 
{
private:
    uint32_t id;
    uint32_t x;
    uint32_t y;
public:
    City(uint32_t id, uint32_t x, uint32_t y) : id(id), x(x), y(y) {}
    std::string to_string() const;
};

} // namespace instance