add_library(Instance STATIC
    City.cpp
    Item.cpp
    Instance.cpp
)

target_include_directories(Instance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
