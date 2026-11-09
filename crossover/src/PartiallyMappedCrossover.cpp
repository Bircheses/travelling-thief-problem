#include <Crossover.hpp>

#include <unordered_map>
#include <stdexcept>

Tour PartiallyMappedCrossover::crossover(const Tour& parent1, const Tour& parent2) {
    uint32_t size = parent1.size();
    if (size < 3) return parent1;

    std::uniform_int_distribution<> dis(0, size - 1);
    uint32_t random_idx1 = dis(rng);
    uint32_t random_idx2 = dis(rng);

    if (random_idx1 > random_idx2) {
        std::swap(random_idx1, random_idx2);
    }

    Tour child(size);

    std::unordered_map<uint32_t, uint32_t> mapping;

    for (size_t i = random_idx1; i <= random_idx2; i++) {
        child[i] = parent1[i];
        mapping[parent1[i]] = parent2[i];
    }

    for (size_t i = 0; i < size; i++) {
        if (i >= random_idx1 && i <= random_idx2) {
            continue;
        }

        uint32_t city = parent2[i];
        while (mapping.find(city) != mapping.end()) {
            city = mapping[city];
        }
        child[i] = city;
    }

    return child;
}
