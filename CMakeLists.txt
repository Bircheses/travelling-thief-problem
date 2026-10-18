cmake_minimum_required(VERSION 3.20)

project(TTP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Instance)
add_subdirectory(core)
add_subdirectory(selection)
add_subdirectory(algorithms)
add_subdirectory(crossover)
add_subdirectory(mutation)

add_executable(TTP main.cpp)
target_link_libraries(TTP PRIVATE Algorithms)
