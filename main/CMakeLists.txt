project(monster_hub)

include(../cmake/compiler_warnings.cmake)
include(../cmake/sanitizers.cmake)

if(MSVC)
    add_compile_options(
        /EHsc
        /GR-)
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(
        -fno-exceptions
        -fno-rtti)
endif()

add_executable(monster_hub
    src/main.cpp)

add_custom_target(run monster_hub
    DEPENDS monster_hub)

