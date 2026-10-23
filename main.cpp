#include "Instance.hpp"
#include "Solution.hpp"
#include "ConfigReader.hpp"
#include "GeneticAlgorithm.hpp"
#include "Writer.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <filesystem>
#include <numeric>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <instance.ttp>" << std::endl;
        return 1;
    }

    instance::Instance inst{};
    inst.load(argv[1]);

    const Config config{};
    const std::string name = std::filesystem::path(argv[1]).stem().string();
    const std::filesystem::path out_dir = "../../output/" + name;
    const unsigned runs = 10;
    const unsigned base_seed = std::chrono::steady_clock::now().time_since_epoch().count();

    std::vector<double> best(runs);
    std::vector<std::thread> threads;

    for (unsigned run = 0; run < runs; run++)
    {
        threads.emplace_back([&, run]() {
            CSVWriter writer(out_dir / ("run_" + std::to_string(run + 1) + ".csv"));
            algorithm::GeneticAlgorithm ga(config, std::move(writer), base_seed + run);
            best[run] = ga.run(inst);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    const double best_overall = *std::max_element(best.begin(), best.end());
    const double worst_overall = *std::min_element(best.begin(), best.end());
    const double average_overall = std::accumulate(best.begin(), best.end(), 0.0) / runs;

    double sum = 0.0;
    for (const double value : best) {
        sum += (value - average_overall) * (value - average_overall);
    }
    const double std_dev = std::sqrt(sum / runs);

    std::ofstream summary_file(out_dir / "summary.csv");

    summary_file << "Best; Worst; Average; Std Dev\n";
    summary_file << best_overall << "; " << worst_overall << "; " << average_overall << "; " << std_dev << "\n";

    summary_file.close();

    return 0;
}
