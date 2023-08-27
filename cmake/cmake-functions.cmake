# include(CMakeParseArguments)

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

# target when running nodejs
function(add_node_executable TARGET)
    add_jsmodule(${TARGET} ${ARGN})

    add_custom_target(
        ${TARGET}_start
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/static/m.js ${CMAKE_BINARY_DIR}/bin/${TARGET}/m.js
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/static/package.json ${CMAKE_BINARY_DIR}/bin/${TARGET}/package.json
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/node_exec.js ${CMAKE_BINARY_DIR}/bin/${TARGET}/node_exec.js
        COMMAND npm run start
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${TARGET}
        COMMENT ${PARSED_ARGS_COMMENT}
    )
endfunction(add_node_executable)

# target when creating an html target (c++ + html)
# serve it as well via python http server
function(add_html TARGET)
    add_jsmodule(${TARGET} ${ARGN})

    add_custom_target(
        ${TARGET}_serve
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/static/index.html ${CMAKE_BINARY_DIR}/bin/${TARGET}/index.html
        COMMAND python3 -m http.server
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET}
        DEPENDS ${TARGET}
    )
endfunction(add_html)

function(add_wasm_test TARGET)
    add_jsmodule(${TARGET} ${ARGN})
    target_link_options(${TARGET} PRIVATE "-sEXIT_RUNTIME=1")
    target_link_libraries(${TARGET} PUBLIC GTest::gtest GTest::gtest_main GTest::gmock)

    add_custom_target(
        ${TARGET}_start
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/static/m.js ${CMAKE_BINARY_DIR}/bin/${TARGET}/m.js
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/static/package.json ${CMAKE_BINARY_DIR}/bin/${TARGET}/package.json
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/static/test_exec.js ${CMAKE_BINARY_DIR}/bin/${TARGET}/node_exec.js
        COMMAND npm run start
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET}
        DEPENDS ${TARGET}
        COMMENT ${PARSED_ARGS_COMMENT}
    )
endfunction(add_wasm_test)
