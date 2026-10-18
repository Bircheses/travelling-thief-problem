#include <Solution.hpp>
#include <Utils.hpp>

#include <random>

#pragma once

class Crossover {
protected:
    std::mt19937 rng;
public:
    Crossover(unsigned seed) : rng(seed) {}
    virtual ~Crossover() = default;
    virtual Tour crossover(const Tour& parent1, const Tour& parent2) = 0;
};

class OrderedCrossover : public Crossover {
public:
    OrderedCrossover(unsigned seed) : Crossover(seed) {}
    Tour crossover(const Tour& parent1, const Tour& parent2) override;
};

class PartiallyMappedCrossover : public Crossover {
public:
    PartiallyMappedCrossover(unsigned seed) : Crossover(seed) {}
    Tour crossover(const Tour& parent1, const Tour& parent2) override;
};

class CycleCrossover : public Crossover {
public:
    CycleCrossover(unsigned seed) : Crossover(seed) {}
    Tour crossover(const Tour& parent1, const Tour& parent2) override;
};