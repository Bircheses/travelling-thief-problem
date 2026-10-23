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

enum class MutationType {
    GENE,
    INDIVIDUAL
};

struct Config {
    Config() = default;

    unsigned pop_size = 300;
    unsigned generations = 600;
    double crossover_rate = 0.75;
    double mutation_rate = 0.25;
    SelectionMethod selection_method = SelectionMethod::TOURNAMENT;
    unsigned tournament_size = 5;
    bool elitarism = true;
    unsigned elite_size = 2;
    TourBuilderMethod tour_builder = TourBuilderMethod::GREEDY;
    BackpackBuilderMethod backpack_builder = BackpackBuilderMethod::GREEDY;
    CrossoverMethod crossover_method = CrossoverMethod::ORDERED;
    MutationMethod mutation_method = MutationMethod::INVERSION;
    MutationType mutation_type = MutationType::GENE;
    bool stagnation = false;
    unsigned max_stagnation = 30;

    static Config load(const std::string& filename);
};

std::string to_string(TourBuilderMethod method);
std::string to_string(BackpackBuilderMethod method);
std::string to_string(SelectionMethod method);
std::string to_string(CrossoverMethod method);
std::string to_string(MutationMethod method);
