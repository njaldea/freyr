project(semantics_test)

add_npm_executable(${PROJECT_NAME} semantics.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest GTest::gmock)
target_link_libraries(${PROJECT_NAME} PRIVATE semantics)

target_link_options(${PROJECT_NAME} PRIVATE "-sEXIT_RUNTIME=1")