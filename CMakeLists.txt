cmake_minimum_required(VERSION 3.12)
project(strange-attractors CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)

find_package(raylib REQUIRED)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(strange-attractors ${SOURCES})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

target_link_libraries(strange-attractors PRIVATE raylib)