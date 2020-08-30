project(unit_tests)

include_directories(../../main/src)

add_executable(unit_tests
    src/math/test_vec2.cpp
    ../../main/src/math/vec2.cpp)
target_link_libraries(unit_tests PRIVATE catch)

add_test(unit_tests unit_tests)

