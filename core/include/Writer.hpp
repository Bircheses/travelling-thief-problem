#include <Solution.hpp>

#include <fstream>
#include <vector>
#include <algorithm>

#pragma once

class GenerationData {
public:
    uint32_t generation;
    double best;
    double average;
    double worst;

    GenerationData(uint32_t gen, const std::vector<Solution>& population)
    {
        generation = gen;
        average = 0.0;
        
        best = std::max_element(population.begin(), population.end())->fitness;
        worst = std::min_element(population.begin(), population.end())->fitness;

        double total_fitness = 0.0;
        for (const auto& sol : population) {
            total_fitness += sol.fitness;
        }
        average = total_fitness / population.size();
    }
    
};

class CSVWriter {
private:
    std::vector<GenerationData> buffer;
public:
    void append(GenerationData data) {
        buffer.push_back(data);
    }

    void write_to_file(const std::string& filename) {
        std::ofstream file("../output/" + filename);
    
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing: " + filename);
        }

        file << "Generation,Best,Average,Worst" << std::endl;

        for (const auto& data : buffer) {
            file << data.generation << "," << data.best << "," << data.average << "," << data.worst << std::endl;
        }
    }

};