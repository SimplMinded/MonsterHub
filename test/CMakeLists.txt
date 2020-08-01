option(ENABLE_TESTS "Enable tests" ON)

if(ENABLE_TESTS)
    enable_testing()

    add_custom_target(test ctest)

    add_subdirectory(unit)
    add_subdirectory(constexpr)

    message(STATUS "Building tests")
endif()

