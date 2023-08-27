find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format-18)
file(GLOB_RECURSE ALL_SOURCE_FILES *.c *.cpp *.h *.hpp)
add_custom_target(format COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${ALL_SOURCE_FILES})