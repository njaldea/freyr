project(main)

# always use add_executable to create the final wasm output
# creating a library needs to be linked with a final executable
# to get a wasm result
# main is not mandatory in an executable
# if main exists, it should be exported as well to silence
# a deadcode warning raised by the compiler
add_executable(${PROJECT_NAME} main.cpp)

# add modularize to disable auto execute
# and be able to `await` to and continue only when
# the module is fully loaded
target_link_options(${PROJECT_NAME} PRIVATE "-sMODULARIZE")
target_link_options(${PROJECT_NAME} PRIVATE "--bind")
