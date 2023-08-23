cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_COMPILER $ENV{EMSDK}/upstream/emscripten/em++)
set(CMAKE_C_COMPILER $ENV{EMSDK}/upstream/emscripten/emcc)

project(freyr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-flto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/freyr.cmake)

add_subdirectory(src)
add_subdirectory(examples)

find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format-18)
file(GLOB_RECURSE ALL_SOURCE_FILES *.c *.cpp *.h *.hpp)
add_custom_target(format COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${ALL_SOURCE_FILES})