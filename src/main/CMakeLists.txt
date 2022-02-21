project(main)

add_executable(${PROJECT_NAME} main.cpp)

# need to manually export methods
target_link_options(${PROJECT_NAME} PRIVATE "-sEXPORTED_FUNCTIONS=_foo,_main")

# add modularize to disable auto execute
# i need to do the following to import the js file

# import { default as MAIN } from './main.js';
# async function main() {
#     const m = await MAIN();
#     console.log(m._foo());
# }
# main();
target_link_options(${PROJECT_NAME} PRIVATE "-sMODULARIZE")
