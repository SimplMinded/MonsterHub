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

include(../cmake/build_options.cmake)

include_directories(src)

set(SRC_FILES
    src/debug/assert.cpp
    src/io/filesystem.cpp
    src/logging/logger.cpp
    src/main.cpp
    src/math/vec2.cpp
    src/rendering/projection.cpp
    src/rendering/renderer.cpp
    src/util/unreachable.cpp
    src/window.cpp)

if(WIN32)
    list(APPEND SRC_FILES
        src/windows.cpp)
elseif(UNIX)
    list(APPEND SRC_FILES
        src/unix.cpp)
else()
    message(FATAL_ERROR "Unsupported target platform")
endif()

add_executable(monster_hub ${SRC_FILES})
target_link_libraries(monster_hub
    PRIVATE glad glfw)

add_custom_target(run monster_hub
    DEPENDS monster_hub)

