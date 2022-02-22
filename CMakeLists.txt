cmake_minimum_required(VERSION 3.16.3)
project(wasm_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WASM "Enable WASM output" ON)

if (WASM)
    add_link_options("-sWASM=1")
else()
    add_link_options("-sWASM=0")
endif()

add_compile_options(-flto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/freki.cmake)

add_subdirectory(src)
add_subdirectory(examples)
