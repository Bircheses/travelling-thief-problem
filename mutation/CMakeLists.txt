add_library(Mutation STATIC
    src/SwapMutation.cpp
    src/InversionMutation.cpp
)
target_include_directories(Mutation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Mutation PUBLIC Core)
