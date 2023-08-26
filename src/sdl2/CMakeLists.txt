project(sdl2)

add_html(${PROJECT_NAME} main.cpp)

target_link_options(${PROJECT_NAME} PRIVATE "-sUSE_SDL=2")
target_link_options(${PROJECT_NAME} PRIVATE "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0")
