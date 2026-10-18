add_library(Core STATIC
    src/ConfigReader.cpp
    src/Solution.cpp
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Core PUBLIC Instance)
