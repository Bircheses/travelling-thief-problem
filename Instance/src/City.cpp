#include "City.hpp"

#include <iostream>
#include <string>

std::string instance::City::to_string() const
{
    std::string s = "{id=" + std::to_string(id) + ", x=" + std::to_string(x) + ", y=" + std::to_string(y) + "}";
    return s;
}