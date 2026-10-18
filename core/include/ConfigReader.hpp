#pragma once

#include <string>

enum class TourBuilderMethod {
    RANDOM,
    GREEDY
};

enum class BackpackBuilderMethod {
    GREEDY
};

enum class SelectionMethod {
    TOURNAMENT,
    ROULETTE,
    ELITIST
};

enum class CrossoverMethod {
    ORDERED,
    PARTIALLY_MAPPED,
    CYCLE
};

enum class MutationMethod {
    SWAP,
    INVERSION
};

struct Config {
    unsigned pop_size = 100;
    unsigned generations = 10;
    double crossover_rate = 0.8;
    double mutation_rate = 0.1;
    SelectionMethod selection_method = SelectionMethod::TOURNAMENT;
    unsigned tournament_size = 5;
    unsigned elite_size = 5;
    TourBuilderMethod tour_builder = TourBuilderMethod::RANDOM;
    BackpackBuilderMethod backpack_builder = BackpackBuilderMethod::GREEDY;
    CrossoverMethod crossover_method = CrossoverMethod::ORDERED;
    MutationMethod mutation_method = MutationMethod::SWAP;

    static Config load(const std::string& filename);
};

std::string to_string(TourBuilderMethod method);
std::string to_string(BackpackBuilderMethod method);
std::string to_string(SelectionMethod method);
std::string to_string(CrossoverMethod method);
std::string to_string(MutationMethod method);
