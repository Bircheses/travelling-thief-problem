#include <Crossover.hpp>

Tour OrderedCrossover::crossover(const Tour& parent1, const Tour& parent2) {
    uint32_t size = parent1.size();
    if (size < 3) return parent1;

    uint32_t span = size - 1;
    auto wrap = [span](uint32_t pos) { return 1 + (pos - 1) % span; };

    std::uniform_int_distribution<> dis(1, size - 1);
    uint32_t random_idx1 = dis(rng);
    uint32_t random_idx2 = dis(rng);

    if (random_idx1 > random_idx2) {
        std::swap(random_idx1, random_idx2);
    }

    Tour child(size);
    std::vector<bool> used(size, false);

    child[0] = parent1[0];
    used[parent1[0]] = true;

    for (size_t i = random_idx1; i <= random_idx2; i++) {
        child[i] = parent1[i];
        used[parent1[i]] = true;
    }

    uint32_t next_pos = wrap(random_idx2 + 1);

    for (size_t i = 0; i < span; i++) {
        uint32_t idx = wrap(random_idx2 + 1 + i);
        if (!used[parent2[idx]]) {
            child[next_pos] = parent2[idx];
            used[parent2[idx]] = true;
            next_pos = wrap(next_pos + 1);
        }
    }

    return child;
}
