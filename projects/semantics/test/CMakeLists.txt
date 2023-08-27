project(semantics_test)

add_wasm_test(${PROJECT_NAME} semantics.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE semantics)
