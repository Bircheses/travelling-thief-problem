add_library(Algorithms STATIC
    GeneticAlgorithm.cpp
    ConfigFactory.cpp
)

target_link_libraries(Algorithms PUBLIC Core Selection Crossover Mutation)

target_include_directories(Algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
