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

## tooling

- install clang-format

> wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -                             <br/>
> echo "deb http://apt.llvm.org/focal/ llvm-toolchain-focal main" | sudo tee -a /etc/apt/sources.list   <br/>
> sudo apt update                                                                                       <br/>
> sudo apt install clang-format-18

## setup kit

> source ./emsdk_env.sh

this should add `EMSDK` env var

## build

> mkdir .build              <br/>
> cmake ..                  <br/>
> cmake .                   <br/>
> make -j                   <br/>

- to format

> make format