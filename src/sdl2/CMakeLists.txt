project(sdl2)

add_html(${PROJECT_NAME} src/main.cpp)

# target_include_directories(
#     ${PROJECT_NAME}
#     PRIVATE
#     includes
# )

target_link_options(${PROJECT_NAME} PRIVATE "-sUSE_SDL=2")
