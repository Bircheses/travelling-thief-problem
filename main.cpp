#include "Instance.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <instance.ttp>" << std::endl;
        return 1;
    }

    instance::Instance inst{};
    inst.load(argv[1]);

    std::cout << inst.to_string() << std::endl;

    return 0;
}
