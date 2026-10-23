# berlin52-ttp\berlin52_n510_bounded-strongly-corr_07.ttp

    unsigned pop_size = 120;
    unsigned generations = 300;
    double crossover_rate = 0.7;
    double mutation_rate = 0.2;
    SelectionMethod selection_method = SelectionMethod::TOURNAMENT;
    unsigned tournament_size = 5;
    bool elitarism = true;
    unsigned elite_size = 2;
    TourBuilderMethod tour_builder = TourBuilderMethod::GREEDY;
    BackpackBuilderMethod backpack_builder = BackpackBuilderMethod::GREEDY;
    CrossoverMethod crossover_method = CrossoverMethod::ORDERED;
    MutationMethod mutation_method = MutationMethod::INVERSION;
    MutationType mutation_type = MutationType::GENE;
    bool stagnation = false;
    unsigned max_stagnation = 30;

# a280_n279_bounded-strongly-corr_07.ttp

    unsigned pop_size = 300;
    unsigned generations = 600;
    double crossover_rate = 0.75;
    double mutation_rate = 0.25;
    SelectionMethod selection_method = SelectionMethod::TOURNAMENT;
    unsigned tournament_size = 5;
    bool elitarism = true;
    unsigned elite_size = 2;
    TourBuilderMethod tour_builder = TourBuilderMethod::GREEDY;
    BackpackBuilderMethod backpack_builder = BackpackBuilderMethod::GREEDY;
    CrossoverMethod crossover_method = CrossoverMethod::ORDERED;
    MutationMethod mutation_method = MutationMethod::INVERSION;
    MutationType mutation_type = MutationType::GENE;
    bool stagnation = false;
    unsigned max_stagnation = 30;

# 