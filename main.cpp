#include "Instance.hpp"
#include "Solution.hpp"
#include "ConfigReader.hpp"
#include "GeneticAlgorithm.hpp"
#include "SimulatedAnnealing.hpp"
#include "Writer.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <filesystem>
#include <numeric>

const uint32_t runs = 10;
const uint32_t random_runs = 10000;

void write_summary(const std::filesystem::path& out_dir, const std::vector<double>& values)
{
    std::filesystem::create_directories(out_dir);

    const double best_overall = *std::max_element(values.begin(), values.end());
    const double worst_overall = *std::min_element(values.begin(), values.end());
    const double average_overall = std::accumulate(values.begin(), values.end(), 0.0) / values.size();

    double sum = 0.0;
    for (const double value : values) {
        sum += (value - average_overall) * (value - average_overall);
    }
    const double std_dev = std::sqrt(sum / values.size());

    std::ofstream summary_file(out_dir / "summary.csv");
    summary_file << "Best; Worst; Average; Std Dev\n";
    summary_file << best_overall << "; " << worst_overall << "; " << average_overall << "; " << std_dev << "\n";
}

template <typename Algorithm>
void run_threaded(const std::filesystem::path& out_dir, const instance::Instance& inst,
                  const Config& config, unsigned base_seed)
{
    std::vector<double> best(runs);
    std::vector<std::thread> threads;

    for (uint32_t run = 0; run < runs; run++) {
        threads.emplace_back([&, run]() {
            CSVWriter writer(out_dir / ("run_" + std::to_string(run + 1) + ".csv"));
            Algorithm algorithm(config, std::move(writer), base_seed + run);
            best[run] = algorithm.run(inst);
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    write_summary(out_dir, best);
}

void sa(std::string name, const instance::Instance& inst, unsigned base_seed)
{
    const std::filesystem::path out_dir = "../../output/" + name + "/sa/";

    Config config{};
    config.tour_builder = TourBuilderMethod::RANDOM;

    run_threaded<algorithm::SimulatedAnnealing>(out_dir, inst, config, base_seed);

    std::cout << "Simulated Annealing completed for instance: " << name << std::endl;
}

void ga(std::string name, const instance::Instance& inst, unsigned base_seed)
{
    const std::filesystem::path out_dir = "../../output/" + name + "/ga/";

    Config config{};

    run_threaded<algorithm::GeneticAlgorithm>(out_dir, inst, config, base_seed);

    std::cout << "Genetic Algorithm completed for instance: " << name << std::endl;
}

void random (std::string name, const instance::Instance& inst, unsigned base_seed)
{
    const std::filesystem::path out_dir = "../../output/" + name + "/random/";

    RandomTourBuilder tour_builder(base_seed);
    GreedyBackpackBuilder backpack_builder;
    const std::vector<bool> backpack = backpack_builder.build(inst);

    std::vector<double> fitness;
    fitness.reserve(random_runs);

    for (uint32_t i = 0; i < random_runs; i++) {
        Solution solution;
        solution.tour = tour_builder.build(inst);
        solution.backpack = backpack;
        fitness.push_back(solution.evaluate(inst));
    }

    write_summary(out_dir, fitness);

    std::cout << "Random Search completed for instance: " << name << std::endl;
}

void greedy(std::string name, const instance::Instance& inst, unsigned base_seed)
{
    const std::filesystem::path out_dir = "../../output/" + name + "/greedy/";

    GreedyTourBuilder tour_builder(base_seed);
    GreedyBackpackBuilder backpack_builder;
    const std::vector<bool> backpack = backpack_builder.build(inst);

    std::vector<double> fitness;
    fitness.reserve(inst.dimension);

    for (uint32_t start = 0; start < inst.dimension; start++) {
        Solution solution;
        solution.tour = tour_builder.build_from(inst, start);
        solution.backpack = backpack;
        fitness.push_back(solution.evaluate(inst));
    }

    write_summary(out_dir, fitness);

    std::cout << "Greedy Search completed for instance: " << name << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <instance.ttp>" << std::endl;
        return 1;
    }

    instance::Instance inst{};
    inst.load(argv[1]);

    const std::string name = std::filesystem::path(argv[1]).stem().string();
    const unsigned base_seed = std::chrono::steady_clock::now().time_since_epoch().count();

    // ga(name, inst, base_seed);
    sa(name, inst, base_seed);
    // random(name, inst, base_seed);
    // greedy(name, inst, base_seed);

    return 0;
}
