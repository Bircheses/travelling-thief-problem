#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>

namespace instance{

struct Instance
{
    std::string problem_name;
    std::string knapsack_data_type;
    uint32_t dimension;
    uint32_t number_of_items;
    uint32_t capacity_of_knapsack;
};

class Loader
{
private:
    Instance instance;
    std::string filename;

public:
    Loader(std::string filename)
    : filename(filename)
    {
    }

    void load()
    {
        std::ifstream file(filename);
        while (file.is_open())
        {
            std::string line;
            std::getline(file, line);
            if (line.find("NAME") != std::string::npos)
            {
                instance.problem_name = line.substr(line.find(":") + 1);
            }
            else if (line.find("TYPE") != std::string::npos)
            {
                instance.knapsack_data_type = line.substr(line.find(":") + 1);
            }
            else if (line.find("DIMENSION") != std::string::npos)
            {
                instance.dimension = std::stoi(line.substr(line.find(":") + 1));
            }
            else if (line.find("NUMBER OF ITEMS") != std::string::npos)
            {
                instance.number_of_items = std::stoi(line.substr(line.find(":") + 1));
            }
            else if (line.find("CAPACITY OF KNAPSACK") != std::string::npos)
            {
                instance.capacity_of_knapsack = std::stoi(line.substr(line.find(":") + 1));
            }
        }
    }

};

} //namespace instance;