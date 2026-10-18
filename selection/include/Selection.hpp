#include <Solution.hpp>
#include <Utils.hpp>
#include <ConfigReader.hpp>

#include <random>

#pragma once

class Selection{
protected:
    const Config& config;
    std::mt19937 rng;
public:
    Selection(const Config& config, unsigned seed) : config(config), rng(seed) {}
    virtual ~Selection() = default;
    virtual const Solution& select(const std::vector<Solution>& population) = 0;

    const Solution& random(const std::vector<Solution>& population) {
        std::uniform_int_distribution<> dis(0, population.size() - 1);
        return population[dis(rng)];
    }
};

class TournamentSelection : public Selection {
    uint32_t tournament_size;
public:
    TournamentSelection(const Config& config, unsigned seed) : Selection(config, seed), tournament_size(config.tournament_size) {}
    const Solution& select(const std::vector<Solution>& population) override;
};

class RouletteSelection : public Selection {
public:
    RouletteSelection(const Config& config, unsigned seed) : Selection(config, seed) {}
    const Solution& select(const std::vector<Solution>& population) override;
};

class ElitistSelection : public Selection {
    uint32_t elite_size;
public:
    ElitistSelection(const Config& config, unsigned seed) : Selection(config, seed), elite_size(config.elite_size) {}
    const Solution& select(const std::vector<Solution>& population) override;
};