# To use cmake extension, do one of the following

----

## setup kit
- Ctrl+p
- `CMake: Edit User-Local CMake Kits`
```json
{
    "name": "Emscripten",
    "compilers": {
      "C": "<path to emsdk>/upstream/emscripten/emcc",
      "CXX": "<path to emsdk>/upstream/emscripten/em++"
    }
}
```

----

## settings.json
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

# To fix intellisense, update c_cpp_properties.json
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
