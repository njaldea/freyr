# freyr

Temporary project containing experimentation with c++ and emscripten. goal is to create a wasm library that contains dear imgui.

## vcpkg

-   ref here: [vcpkg](https://vcpkg.io/en/getting-started.html)
-   create environment variable
    -   `export VCPKG=<path>`
-   create vcpkg.json
    -   add the package to vcpkg.json
    -   install the package via `$VCPKG/vcpkg install`
    -   then check the version and add it if necessary
    -   TODO: look for easier way to specify the version
-   add to CMakeLists.txt
    -   `include($ENV{VCPKG}/scripts/buildsystems/vcpkg.cmake)`
    -   `find_package(imgui CONFIG REQUIRED)`
-   some apt packages might need to be installed.
    -   install until requested by vcpkg
    -   `sudo apt-get install pkg-config`

## emscripten

-   ref here: [emscripten](https://emscripten.org/docs/getting_started/downloads.html)

```shell
source ./emsdk_env.sh
```

this should add `EMSDK` env var

## tooling

-   install clang-format

```shell
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
echo "deb http://apt.llvm.org/focal/ llvm-toolchain-focal main" | sudo tee -a /etc/apt/sources.list
sudo apt update
sudo apt install clang-format-18
```

## setting up cmake

```cmake
# this will setup the toolchain
include($ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
# this will setup the target to be used by vcpkg
set(VCPKG_TARGET_TRIPLET wasm32-emscripten)
# this will include vcpkg tooling
include($ENV{VCPKG}/scripts/buildsystems/vcpkg.cmake)
# this will find the library that might be provided by vcpkg
find_package(<library> CONFIG REQUIRED)
```

## build

```shell
mkdir .build
cmake ..
make -j
make format
```

## guidelines for targets

-   `add_jsmodule(NAME ...)`
    -   will create target `NAME`
    -   will create `index.mjs` and `index.wasm`
-   `add_html(NAME ...)`:
    -   call `add_jsmodule`
    -   will create target `NAME` and `NAME_serve`
    -   create a target with suffix `_serve` which will setup the server
-   `add_node_executable(NAME ...)`
    -   call `add_jsmodule`
    -   will create target `NAME` and `NAME_run`
    -   create a target with suffix `_node` which will execute `node_exec.js`
    -   make sure to have `node_exec.js`.
-   `add_wasm_test(NAME ...)`
    -   call `add_jsmodule`
    -   will create target `NAME` and `NAME_run`
    -   will register to ctest as `NAME`
    -   make sure to split emscripten bindings to vanilla js library
    -   only test the vanilla c++ libraries

### TODO

-   modules can't be destroyed, causing leak
    -   when imgui is created, wasm resources are not released. things done:
        -   stop runtime (via `emscripten_force_exit` call)
        -   references to the module is set to null
-   for libraries (non-canvas dependent):
    -   js glue code always have canvas references. figure out how to ship minimal js/wasm if possible.
