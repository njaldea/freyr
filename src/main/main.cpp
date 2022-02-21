#include <iostream>

#include <emscripten.h>
#include <unordered_map>

extern "C"
{
    /**
     * EMSCRIPTEN_KEEPALIVE will automatically export the method
     */
    int EMSCRIPTEN_KEEPALIVE foo()
    {
        std::cout << "foo hello, world!\n";
        return 0;
    }
}
