add_library(Instance STATIC
    src/City.cpp
    src/Item.cpp
    src/Instance.cpp
)

target_include_directories(Instance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
