project(example-demo)

add_npm_executable(
    TARGET example-demo-start
    ARGS start
    DEPENDS semantics
    COMMENT "RUNNING DEMO"
)
