# To use cmake extension, do one of the following

----

## tooling
- install clang-format

> wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
> echo "deb http://apt.llvm.org/focal/ llvm-toolchain-focal main" | sudo tee -a /etc/apt/sources.list
> sudo apt update
> sudo apt install clang-format-18

## setup kit
> source ./emsdk_env.sh
this should add `EMSDK` env var

----

## settings.json (not sure if used)
- add the following
```json
{
    "cmake.configureArgs": [ "--experimental-wasm-threads" ],
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "<path to emsdk>/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake",
        "CMAKE_CROSSCOMPILING_EMULATOR": "<path to emsdk>/node/14.18.2_64bit/bin/node"
    },
}
```

the configuration above is normally set up by `emcmake` wrapper

# To fix intellisense, update c_cpp_properties.json (now in workspace)
- set compiler path
```json
{
    "configurations": [
        {
            "name": "Emscripten",
            "cStandard": "gnu17",
            "cppStandard": "c++20",
            "intelliSenseMode": "linux-clang-x64",
            "compilerPath": "<path to emsdk>/emsdk/upstream/emscripten/em++",
            "compileCommands": "${workspaceFolder}/.build/compile_commands.json",
            "configurationProvider": "ms-vscode.cmake-tools"
        }
    ],
    "version": 4
}
```
