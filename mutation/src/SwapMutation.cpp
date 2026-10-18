#include <Mutation.hpp>

void SwapMutation::mutate(Tour& tour) {
    uint32_t size = tour.size();
    if (size < 3) return;

    std::uniform_int_distribution<> dis(1, size - 1);
    uint32_t idx1 = dis(rng);
    uint32_t idx2 = dis(rng);

    while (idx1 == idx2) {
        idx2 = dis(rng);
    }

    std::swap(tour[idx1], tour[idx2]);
}
