include(CMakeParseArguments)

function(add_npm_run_target)
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
endfunction(add_npm_run_target)
