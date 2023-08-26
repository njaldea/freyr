#include <iostream>

#include <emscripten.h>

#include <unordered_map>

#include <memory>

extern "C"
{
    int EMSCRIPTEN_KEEPALIVE foo(int x);
}

struct ValueObject
{
    int x;
    ValueObject(int _x);
    ValueObject();
    ~ValueObject();
};

struct ValueArray
{
    int x;
    ValueArray(int _x);
    ValueArray();
    ~ValueArray();
};

ValueObject non_c_function_object();

ValueArray non_c_function_array();

class Freyr
{
public:
    Freyr();
    ~Freyr();
    void foo(int x);
};

class Freki
{
public:
    Freki();
    ~Freki();
    void foo(Freyr& f);
    void fizz(ValueObject& v);
    void fuzz(ValueArray& v);
};
