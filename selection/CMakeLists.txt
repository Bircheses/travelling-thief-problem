add_library(Selection STATIC
    src/TournamentSelection.cpp
    src/RouletteSelection.cpp
    src/ElitistSelection.cpp
)
target_include_directories(Selection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Selection PUBLIC Core)
