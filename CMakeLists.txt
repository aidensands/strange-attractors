cmake_minimum_required(VERSION 3.12)
project(strange-attractors CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)

find_package(raylib REQUIRED)
add_executable(strange-attractors src/main.cpp)

target_link_libraries(strange-attractors PRIVATE raylib)