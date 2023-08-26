cmake_minimum_required(VERSION 3.16.3)

include($ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)

project(freyr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-flto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(VCPKG_TARGET_TRIPLET wasm32-emscripten)

include(cmake/freyr.cmake)
include($ENV{VCPKG}/scripts/buildsystems/vcpkg.cmake)

find_package(GTest CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(src)

find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format-18)
file(GLOB_RECURSE ALL_SOURCE_FILES *.c *.cpp *.h *.hpp)
add_custom_target(format COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${ALL_SOURCE_FILES})