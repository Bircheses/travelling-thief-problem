add_library(Crossover STATIC
    src/CycleCrossover.cpp
    src/OrderedCrossover.cpp
    src/PartiallyMappedCrossover.cpp
)
target_include_directories(Crossover PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Crossover PUBLIC Core)