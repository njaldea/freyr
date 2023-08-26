include(CMakeParseArguments)

# helper function to move all files of a binary to its own directory
function(set_freyr_target_properties TARGET)
    set_target_properties(
        ${TARGET}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${TARGET}"
    )
endfunction(set_freyr_target_properties)

# target when running nodejs
function(add_npm_executable)
    cmake_parse_arguments(
        PARSED_ARGS         # prefix of output variables
        ""                  # list of names of the boolean arguments (only defined ones will be true)
        "TARGET;COMMENT"    # list of names of mono-valued arguments
        "DEPENDS;ARGS"      # list of names of multi-valued arguments (output variables are lists)
        ${ARGN}             # arguments of the function to parse, here we take the all original ones
    )

    add_custom_target(
        ${PARSED_ARGS_TARGET}
        COMMAND npm run ${PARSED_ARGS_ARGS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${PARSED_ARGS_DEPENDS}
        COMMENT ${PARSED_ARGS_COMMENT}
    )
endfunction(add_npm_executable)

# target when creating a js library from c++
function(add_jsmodule TARGET)
    add_executable(${TARGET} ${ARGN})
    set_freyr_target_properties(${TARGET})

    target_link_options(${TARGET} PRIVATE "-sWASM=2")
    target_link_options(${TARGET} PRIVATE "-sMODULARIZE")
    # target_link_options(${TARGET} PRIVATE "-sSTANDALONE_WASM")
    # target_link_options(${TARGET} PRIVATE "-sMINIMAL_RUNTIME=1")
    target_link_options(${TARGET} PRIVATE "-sEXPORT_NAME='${TARGET}'")
    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME "index" SUFFIX ".mjs")
endfunction(add_jsmodule)

# target when creating an html target (c++ + html)
# serve it as well via python http server
function(add_html TARGET)
    add_executable(${TARGET} ${ARGN})
    set_freyr_target_properties(${TARGET})
    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME "index" SUFFIX ".html")

    add_custom_target(
        ${TARGET}-serve
        COMMAND python3 -m http.server
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET}
        DEPENDS ${TARGET}
    )
endfunction(add_html)