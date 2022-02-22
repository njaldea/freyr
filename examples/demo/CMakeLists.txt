project(example-demo)

add_npm_run_target(
    TARGET example-demo-start
    ARGS start
    DEPENDS main
    COMMENT "RUNNING DEMO"
)
