#include <Selection.hpp>

#include <algorithm>

const Solution& TournamentSelection::select(const std::vector<Solution>& population)
{
    const Solution* best = &random(population);

    for (size_t i = 0; i < tournament_size - 1; i++) {
        const Solution& contestant = random(population);
        if (*best < contestant) 
        {
            best = &contestant;
        }
    }

    return *best;
}