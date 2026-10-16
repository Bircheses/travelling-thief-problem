cmake_minimum_required(VERSION 3.20)

project(TTP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ConfigReader STATIC
    ConfigReader.cpp
    ConfigReader.hpp
)
target_include_directories(ConfigReader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Instance)
add_subdirectory(Algorithms)

add_executable(TTP main.cpp
    ConfigReader.cpp
    ConfigReader.hpp)
target_link_libraries(TTP PRIVATE Instance Algorithms ConfigReader)