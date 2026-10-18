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

static SelectionMethod parseSelectionMethod(const std::string& s, SelectionMethod fallback)
{
    if (s == "tournament") return SelectionMethod::TOURNAMENT;
    if (s == "roulette")   return SelectionMethod::ROULETTE;
    if (s == "elitist")    return SelectionMethod::ELITIST;
    std::cerr << "Warning: unknown selection_method \"" << s << "\", using " << to_string(fallback) << '\n';
    return fallback;
}

static TourBuilderMethod parseTourBuilderMethod(const std::string& s, TourBuilderMethod fallback)
{
    if (s == "random") return TourBuilderMethod::RANDOM;
    if (s == "greedy") return TourBuilderMethod::GREEDY;
    std::cerr << "Warning: unknown tour_builder \"" << s << "\", using " << to_string(fallback) << '\n';
    return fallback;
}

static BackpackBuilderMethod parseBackpackBuilderMethod(const std::string& s, BackpackBuilderMethod fallback)
{
    if (s == "greedy") return BackpackBuilderMethod::GREEDY;
    std::cerr << "Warning: unknown backpack_builder \"" << s << "\", using " << to_string(fallback) << '\n';
    return fallback;
}

static CrossoverMethod parseCrossoverMethod(const std::string& s, CrossoverMethod fallback)
{
    if (s == "ordered")          return CrossoverMethod::ORDERED;
    if (s == "partially_mapped") return CrossoverMethod::PARTIALLY_MAPPED;
    if (s == "cycle")            return CrossoverMethod::CYCLE;
    std::cerr << "Warning: unknown crossover_method \"" << s << "\", using " << to_string(fallback) << '\n';
    return fallback;
}

static MutationMethod parseMutationMethod(const std::string& s, MutationMethod fallback)
{
    if (s == "swap")      return MutationMethod::SWAP;
    if (s == "inversion") return MutationMethod::INVERSION;
    std::cerr << "Warning: unknown mutation_method \"" << s << "\", using " << to_string(fallback) << '\n';
    return fallback;
}

std::string to_string(SelectionMethod method)
{
    switch (method) {
        case SelectionMethod::TOURNAMENT: return "tournament";
        case SelectionMethod::ROULETTE:   return "roulette";
        case SelectionMethod::ELITIST:    return "elitist";
    }
    return "unknown";
}

std::string to_string(TourBuilderMethod method)
{
    switch (method) {
        case TourBuilderMethod::RANDOM: return "random";
        case TourBuilderMethod::GREEDY: return "greedy";
    }
    return "unknown";
}

std::string to_string(BackpackBuilderMethod method)
{
    switch (method) {
        case BackpackBuilderMethod::GREEDY: return "greedy";
    }
    return "unknown";
}

std::string to_string(CrossoverMethod method)
{
    switch (method) {
        case CrossoverMethod::ORDERED:          return "ordered";
        case CrossoverMethod::PARTIALLY_MAPPED: return "partially_mapped";
        case CrossoverMethod::CYCLE:            return "cycle";
    }
    return "unknown";
}

std::string to_string(MutationMethod method)
{
    switch (method) {
        case MutationMethod::SWAP:      return "swap";
        case MutationMethod::INVERSION: return "inversion";
    }
    return "unknown";
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
    if (kv.count("selection_method")) cfg.selection_method = parseSelectionMethod(kv["selection_method"], cfg.selection_method);
    if (kv.count("tournament_size"))  cfg.tournament_size = std::stoul(kv["tournament_size"]);
    if (kv.count("elite_size"))       cfg.elite_size = std::stoul(kv["elite_size"]);
    if (kv.count("tour_builder"))     cfg.tour_builder = parseTourBuilderMethod(kv["tour_builder"], cfg.tour_builder);
    if (kv.count("backpack_builder")) cfg.backpack_builder = parseBackpackBuilderMethod(kv["backpack_builder"], cfg.backpack_builder);
    if (kv.count("crossover_method")) cfg.crossover_method = parseCrossoverMethod(kv["crossover_method"], cfg.crossover_method);
    if (kv.count("mutation_method"))  cfg.mutation_method = parseMutationMethod(kv["mutation_method"], cfg.mutation_method);

    return cfg;
}
