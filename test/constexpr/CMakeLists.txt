project(constexpr_tests)

set(SRC_FILES
    src/dummy.cpp)

add_executable(constexpr_tests ${SRC_FILES})
target_link_libraries(constexpr_tests PRIVATE catch)

add_test(constexpr_tests constexpr_tests)

add_executable(constexpr_relaxed_tests ${SRC_FILES})
target_link_libraries(constexpr_relaxed_tests PRIVATE catch)
target_compile_definitions(constexpr_relaxed_tests PRIVATE
    -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

