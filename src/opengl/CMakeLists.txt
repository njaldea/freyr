project(opengl)

add_html(
    ${PROJECT_NAME}
    glbook.cpp
    esUtil.c
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    includes
)
