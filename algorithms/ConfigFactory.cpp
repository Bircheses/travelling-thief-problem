#include <ConfigFactory.hpp>

#include <stdexcept>

std::unique_ptr<TourBuilder> ConfigFactory::make_tour_builder()
{
    switch (config.tour_builder) {
        case TourBuilderMethod::RANDOM: return std::make_unique<RandomTourBuilder>(rng());
        case TourBuilderMethod::GREEDY: return std::make_unique<GreedyTourBuilder>(rng());
    }
    throw std::invalid_argument("Unknown tour builder: " + to_string(config.tour_builder));
}

std::unique_ptr<BackpackBuilder> ConfigFactory::make_backpack_builder()
{
    switch (config.backpack_builder) {
        case BackpackBuilderMethod::GREEDY: return std::make_unique<GreedyBackpackBuilder>();
    }
    throw std::invalid_argument("Unknown backpack builder: " + to_string(config.backpack_builder));
}

std::unique_ptr<Selection> ConfigFactory::make_selection()
{
    switch (config.selection_method) {
        case SelectionMethod::TOURNAMENT: return std::make_unique<TournamentSelection>(config, rng());
        case SelectionMethod::ROULETTE: return std::make_unique<RouletteSelection>(config, rng());
        case SelectionMethod::ELITIST: return std::make_unique<ElitistSelection>(config, rng());
    }
    throw std::invalid_argument("Unknown selection method: " + to_string(config.selection_method));
}

std::unique_ptr<Crossover> ConfigFactory::make_crossover()
{
    switch (config.crossover_method) {
        case CrossoverMethod::ORDERED: return std::make_unique<OrderedCrossover>(rng());
        case CrossoverMethod::PARTIALLY_MAPPED: return std::make_unique<PartiallyMappedCrossover>(rng());
        case CrossoverMethod::CYCLE: return std::make_unique<CycleCrossover>(rng());
    }
    throw std::invalid_argument("Unknown crossover method: " + to_string(config.crossover_method));
}

std::unique_ptr<Mutation> ConfigFactory::make_mutation()
{
    switch (config.mutation_method) {
        case MutationMethod::SWAP: return std::make_unique<SwapMutation>(rng());
        case MutationMethod::INVERSION: return std::make_unique<InversionMutation>(rng());
    }
    throw std::invalid_argument("Unknown mutation method: " + to_string(config.mutation_method));
}
