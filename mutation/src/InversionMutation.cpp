#include <Mutation.hpp>

#include <algorithm>

void InversionMutation::mutate(Tour& tour) {
    uint32_t size = tour.size();
    if (size < 3) return;

    std::uniform_int_distribution<> dis(1, size - 1);
    uint32_t idx1 = dis(rng);
    uint32_t idx2 = dis(rng);

    while(idx1 == idx2) {
        idx2 = dis(rng);
    }

    auto min_idx = std::min(idx1, idx2);
    auto max_idx = std::max(idx1, idx2);
    std::reverse(tour.begin() + min_idx, tour.begin() + max_idx + 1);
}
