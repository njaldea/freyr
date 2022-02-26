include(CMakeParseArguments)

function(set_freyr_target_properties TARGET)
    set_target_properties(
        ${TARGET}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${TARGET}"
    )
endfunction(set_freyr_target_properties)

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

function(add_jsmodule TARGET)
    add_executable(${TARGET} ${ARGN})
    set_freyr_target_properties(${TARGET})

    # add modularize to disable auto execute
    # and be able to `await` to and continue only when
    # the module is fully loaded
    target_link_options(${TARGET} PRIVATE "-sMODULARIZE")
    target_link_options(${TARGET} PRIVATE "-sWASM=1")
    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME "index" SUFFIX ".js")
endfunction(add_jsmodule)

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