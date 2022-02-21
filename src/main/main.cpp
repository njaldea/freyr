#include <iostream>

#include <emscripten.h>
#include <unordered_map>

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    int foo()
    {
        std::cout << "foo hello, world!\n";
        return 0;
    }
}

int main()
{
    std::unordered_map<int, int> m;
    for (const auto &[k, v] : m)
    {
    }

    std::cout << "main hello, world!\n";
    return 0;
}