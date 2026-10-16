#include "ConfigReader.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

static std::string trim(const std::string& s)
{
    const char* ws = " \t\r\n\"";
    size_t b = s.find_first_not_of(ws);
    size_t e = s.find_last_not_of(ws);
    return b == std::string::npos ? "" : s.substr(b, e - b + 1);
}

Config Config::load(const std::string& filename)
{
    Config cfg;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: could not open " << filename << ", using defaults\n";
        return cfg;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    text = text.substr(text.find('{') + 1, text.rfind('}') - text.find('{') - 1);

    std::map<std::string, std::string> kv;
    std::stringstream ss(text);
    std::string pair;
    while (std::getline(ss, pair, ',')) {
        size_t colon = pair.find(':');
        if (colon == std::string::npos) continue;
        kv[trim(pair.substr(0, colon))] = trim(pair.substr(colon + 1));
    }

    if (kv.count("pop_size"))         cfg.pop_size = std::stoul(kv["pop_size"]);
    if (kv.count("generations"))      cfg.generations = std::stoul(kv["generations"]);
    if (kv.count("crossover_rate"))   cfg.crossover_rate = std::stod(kv["crossover_rate"]);
    if (kv.count("mutation_rate"))    cfg.mutation_rate = std::stod(kv["mutation_rate"]);
    if (kv.count("selection_method")) cfg.selection_method = kv["selection_method"];
    if (kv.count("tour_builder"))     cfg.tour_builder = kv["tour_builder"];

    return cfg;
}
