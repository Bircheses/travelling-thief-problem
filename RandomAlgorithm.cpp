#include "Instance.hpp"

#include <vector>
#include <cstdint>

namespace algorithms {
   
// class Solution {
//     virtual void evaluate(const Instance& instance) = 0; // Pure virtual function to evaluate the solution based on the instance data{
//         // Evaluate the solution based on the instance data
//     }
// };

// class TSPSolution : public Solution {
//     void evaluate() override {
//         // Evaluate the TSP solution based on the instance data
//     }
// };

// class KNPSolution : public Solution {
//     void evaluate() override {
//         // Evaluate the KNPsolution based on the instance data
//     }
// };

class Invidual {
public:
    Invidual() : tsp_eval(0.0), knp_eval(0.0), tour() {}
    double tsp_eval;
    double knp_eval;
    std::vector<uint32_t> tour;
};

class Algorithm {
public:
    virtual Invidual run(instance::Instance instance) const = 0;
};

class RandomAlgorithm : Algorithm {
private:
    instance::Instance instance;
public:
    Invidual run(instance::Instance instance) const override;
};

Invidual RandomAlgorithm::run(instance::Instance instance) const {
    Invidual invidual;

    // fill from index 0 to instance.dimension - 1

    // Then shuffle the vector to create a random tour
    
    return invidual;
}

} // namespace algorithms