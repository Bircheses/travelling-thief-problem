#include <Utils.hpp>

#include <random>

#pragma once

class Mutation {
protected:
    std::mt19937 rng;
public:
    Mutation(unsigned seed) : rng(seed) {}
    virtual ~Mutation() = default;
    virtual void mutate(Tour& tour) = 0;
};

class SwapMutation : public Mutation {
public:
    SwapMutation(unsigned seed) : Mutation(seed) {}
    void mutate(Tour& tour) override;
};

class InversionMutation : public Mutation {
public:
    InversionMutation(unsigned seed) : Mutation(seed) {}
    void mutate(Tour& tour) override;
};
