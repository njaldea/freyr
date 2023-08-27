project(semantics)

add_library(${PROJECT_NAME} semantics.cpp)
target_link_options(${PROJECT_NAME} PUBLIC "--bind")

add_node_executable(${PROJECT_NAME}_js bindings.cpp)
target_link_libraries(${PROJECT_NAME}_js PRIVATE ${PROJECT_NAME})

add_subdirectory(test)