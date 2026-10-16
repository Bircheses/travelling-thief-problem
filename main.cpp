#include "Instance.hpp"
#include "algorithms/Builders.hpp"
#include "algorithms/Solution.hpp"

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
    RandomTourBuilder tour_builder(seed);

    Solution solution;
    solution.tour = GreedyTourBuilder().build(inst);
    solution.backpack = GreedyBackpackBuilder().build(inst);
    solution.evaluate(inst);

    std::cout << "Tour: ";
    for (const auto& city : solution.tour) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "Backpack: ";
    for (const auto& item : solution.backpack) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << "Fitness: " << solution.fitness << std::endl;

    return 0;
}
