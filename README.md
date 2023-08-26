# freyr

Temporary project containing experimentation with c++ and emscripten. goal is to create a wasm library that contains dear imgui.

## vcpkg

- ref here: [vcpkg](https://vcpkg.io/en/getting-started.html)
- create environment variable
    - `export VCPKG=<path>`
- create vcpkg.json
    - add the package to vcpkg.json
    - install the package via `$VCPKG/vcpkg install`
    - then check the version and add it if necessary
    - TODO: look for easier way to specify the version
- add to CMakeLists.txt
    - `include($ENV{VCPKG}/scripts/buildsystems/vcpkg.cmake)`
    - `find_package(imgui CONFIG REQUIRED)`
- some apt packages might need to be installed.
    - install until requested by vcpkg
    - `sudo apt-get install pkg-config`

## emscripten

- ref here: [emscripten](https://emscripten.org/docs/getting_started/downloads.html)

```shell
source ./emsdk_env.sh
```

this should add `EMSDK` env var

## tooling

- install clang-format

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

- `add_jsmodule`
    - will create `index.mjs` and `index.wasm`
- `add_html`:
    - call `add_jsmodule`
    - create a target with suffix `_serve` which will setup the server
- `add_npm_executable`
    - call `add_jsmodule`
    - create a target with suffix `_node` which will execute `node_exec.js`
    - make sure to have `node_exec.js`.
- when writing tests for c++ libraries
    - make sure to split emscripten bindings to vanilla js library
    - only test the vanilla js library

```cpp
int main() {
    testing::InitGoogleTest();
    emscripten_force_exit(RUN_ALL_TESTS());
}
```

```javascript
// this library is a wrapper to load the js/wasm modules produced by add_jsmodule
import m from './m.js';

// TODO: hide this to cmake function:
//  - maybe by creating a separate `node_exec.js` that will be copied specifically for tests
```
