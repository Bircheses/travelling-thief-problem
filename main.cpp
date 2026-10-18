#include "Instance.hpp"
#include "Solution.hpp"
#include "ConfigReader.hpp"
#include "GeneticAlgorithm.hpp"

#include <chrono>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <instance.ttp>" << std::endl;
        return 1;
    }

    instance::Instance inst{};
    inst.load(argv[1]);

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::cout << "Seed: " << seed << '\n';
    Config config = Config::load("../config.json");
    std::cout << "Tour builder: " << to_string(config.tour_builder)
              << ", selection: " << to_string(config.selection_method)
              << ", crossover: " << to_string(config.crossover_method)
              << ", mutation: " << to_string(config.mutation_method) << '\n';

    algorithm::GeneticAlgorithm ga(config, seed);
    Solution best = ga.run(inst);

    std::cout << "Tour: ";
    for (const auto& city : best.tour) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "Backpack: ";
    for (const auto& item : best.backpack) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << "Fitness: " << best.fitness << std::endl;

    return 0;
}
