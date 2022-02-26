project(semantics)

# always use add_executable to create the final wasm output
# creating a library needs to be linked with a final executable
# to get a wasm result
# main is not mandatory in an executable
# if main exists, it should be exported as well to silence
# a deadcode warning raised by the compiler
add_jsmodule(
    ${PROJECT_NAME}
    src/semantics.cpp
)

target_link_options(${PROJECT_NAME} PRIVATE "--bind")

add_html(
    ${PROJECT_NAME}-html
    src/semantics.cpp
)

target_link_options(${PROJECT_NAME}-html PRIVATE "--bind")
