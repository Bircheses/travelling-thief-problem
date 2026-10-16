add_library(Algorithms STATIC
    Builders.hpp
    Solution.hpp
    GeneticAlgorithm.cpp
    Operators.hpp
    Utils.hpp
)

target_link_libraries(Algorithms PUBLIC Instance ConfigReader)

target_include_directories(Algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
