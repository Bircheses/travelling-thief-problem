#include <Crossover.hpp>

Tour OrderedCrossover::crossover(const Tour& parent1, const Tour& parent2) {
    uint32_t size = parent1.size();
    if (size < 3) return parent1;

    std::uniform_int_distribution<> dis(0, size - 1);
    uint32_t random_idx1 = dis(rng);
    uint32_t random_idx2 = dis(rng);

    if (random_idx1 > random_idx2) {
        std::swap(random_idx1, random_idx2);
    }

    Tour child(size);
    std::vector<bool> used(size, false);

    for (size_t i = random_idx1; i <= random_idx2; i++) {
        child[i] = parent1[i];
        used[parent1[i]] = true;
    }

    uint32_t next_pos = (random_idx2 + 1) % size;
    for (size_t i = 0; i < size; i++) {
        uint32_t city = parent2[(random_idx2 + 1 + i) % size];
        if (!used[city]) {
            child[next_pos] = city;
            used[city] = true;
            next_pos = (next_pos + 1) % size;
        }
    }

    return child;
}
