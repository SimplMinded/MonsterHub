project(catch2)

add_library(catch STATIC src/main.cpp)
target_include_directories(catch PUBLIC include)

