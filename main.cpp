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
    Config config = Config::load("../config.json");

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
