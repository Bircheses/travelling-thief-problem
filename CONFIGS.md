## Shared settings (all instances)

    double crossover_rate = 0.8;
    double mutation_rate = 0.3;
    SelectionMethod selection_method = SelectionMethod::TOURNAMENT;
    unsigned tournament_size = 5;
    bool elitarism = true;
    unsigned elite_size = 2;
    TourBuilderMethod tour_builder = TourBuilderMethod::GREEDY;
    BackpackBuilderMethod backpack_builder = BackpackBuilderMethod::GREEDY;
    CrossoverMethod crossover_method = CrossoverMethod::ORDERED;
    MutationMethod mutation_method = MutationMethod::INVERSION;
    MutationType mutation_type = MutationType::INDIVIDUAL;
    bool stagnation = false;
    unsigned max_stagnation = 30;

---

# berlin52-ttp\berlin52_n510_bounded-strongly-corr_07.ttp

    // GA
    unsigned pop_size = 100;
    unsigned generations = 500;

    // SA
    double initial_temperature = 5200.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.995;
    uint32_t iterations_per_temperature = 52;

# pr76-ttp\pr76_n750_bounded-strongly-corr_07.ttp

    // GA
    unsigned pop_size = 150;
    unsigned generations = 500;

    // SA
    double initial_temperature = 7600.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.995;
    uint32_t iterations_per_temperature = 76;

# gil262-ttp\gil262_n261_uncorr-similar-weights_07.ttp

    // GA
    unsigned pop_size = 200;
    unsigned generations = 1000;

    // SA
    double initial_temperature = 5240.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.99;
    uint32_t iterations_per_temperature = 262;

# a280-ttp\a280_n279_bounded-strongly-corr_07.ttp

    // GA
    unsigned pop_size = 200;
    unsigned generations = 1000;

    // SA
    double initial_temperature = 5600.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.99;
    uint32_t iterations_per_temperature = 280;

# rd400-ttp\rd400_n399_bounded-strongly-corr_07.ttp

    // GA
    unsigned pop_size = 250;
    unsigned generations = 1000;

    // SA
    double initial_temperature = 4000.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.99;
    uint32_t iterations_per_temperature = 400;

# d493-ttp\d493_n492_uncorr_07.ttp

    // GA
    unsigned pop_size = 250;
    unsigned generations = 1000;

    // SA
    double initial_temperature = 4930.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.99;
    uint32_t iterations_per_temperature = 493;

# pcb442-ttp\pcb442_n1323_bounded-strongly-corr_05.ttp

    // GA
    unsigned pop_size = 250;
    unsigned generations = 1000;

    // SA
    double initial_temperature = 4420.0;
    double final_temperature = 0.1;
    double cooling_rate = 0.99;
    uint32_t iterations_per_temperature = 442;
