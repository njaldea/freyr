what to change:
- in vscode compiler settings. set compiler manually: `<emsdk>/upstream/emscripten/em++`. This will fix the include headers for emscripten.

what to setup:
- configuring cmake should be done via emcmake wrapper. after this, everything should work normally.
- emcmake cmake <repo path>
- make ...

when compiled with html, we can view the it by launching an http server
- python3 -m http.server