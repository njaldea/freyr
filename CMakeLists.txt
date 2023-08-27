cmake_minimum_required(VERSION 3.16.3)

# this sets emscripten compiler and needs to be called before project() to avoid infinite loop
include(cmake/toolchain.cmake)

project(freyr CXX)

include(cmake/vcpkg.cmake)
include(cmake/clang-format.cmake)
include(cmake/cmake-functions.cmake)

find_package(GTest CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(projects)
