project(imgui)

add_jsmodule(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)

target_link_options(${PROJECT_NAME} PRIVATE "-sUSE_SDL=2")
target_link_options(${PROJECT_NAME} PRIVATE "-ALLOW_MEMORY_GROWTH=1")
target_link_options(${PROJECT_NAME} PRIVATE "-ASSERTIONS=1")
target_link_options(${PROJECT_NAME} PRIVATE "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0")