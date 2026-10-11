#include "City.hpp"

std::string instance::City::to_string() const
{
    return "{id=" + std::to_string(id) + ", x=" + std::to_string(x) + ", y=" + std::to_string(y) + "}";
}