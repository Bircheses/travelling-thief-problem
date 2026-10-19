#include "Instance.hpp"
#include "Solution.hpp"
#include "ConfigReader.hpp"
#include "GeneticAlgorithm.hpp"
#include "Writer.hpp"

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
    CSVWriter writer = CSVWriter();

    algorithm::GeneticAlgorithm ga(config, writer, seed);
    Solution best = ga.run(inst);

    return 0;
}
