project(semantics)

add_npm_executable(${PROJECT_NAME} src/semantics.cpp)

target_link_options(${PROJECT_NAME} PRIVATE "--bind")
