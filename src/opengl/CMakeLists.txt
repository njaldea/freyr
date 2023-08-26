project(opengl)

add_jsmodule(
    ${PROJECT_NAME}
    src/glbook.cpp
    src/esUtil.c
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    includes
)
