cmake_minimum_required(VERSION 3.12)

project(MonsterHub)

set(CMAKE_CXX_STANDARD 17)
message(STATUS "Building with c++${CMAKE_CXX_STANDARD} support")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")

add_subdirectory(vendor)
add_subdirectory(main)
add_subdirectory(test)

