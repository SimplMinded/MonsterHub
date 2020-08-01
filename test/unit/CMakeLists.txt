project(unit_tests)

add_executable(unit_tests
    src/dummy.cpp)
target_link_libraries(unit_tests PRIVATE catch)

add_test(unit_tests unit_tests)

