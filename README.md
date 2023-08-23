# freyr

Temporary project containing experimentation with c++ and emscripten. goal is to create a wasm library that contains dear imgui.

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
> make -j                   <br/>

- to format

> make format