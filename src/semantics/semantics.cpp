#include <iostream>

#include "semantics.hpp"

extern "C"
{
    /**
     * EMSCRIPTEN_KEEPALIVE will automatically export the method
     */
    int EMSCRIPTEN_KEEPALIVE foo(int x)
    {
        std::cout << x << ": foo hello, world!\n";
        return 0;
    }
}

ValueObject::ValueObject(int _x)
    : x(_x)
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

ValueObject::ValueObject()
    : ValueObject(100)
{
}

ValueObject::~ValueObject()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

ValueArray::ValueArray(int _x)
    : x(_x)
{
    std::cout << __FILE__ //
              << ":"      //
              << __LINE__ //
              << ":"      //
              << __FUNCTION__ << std::endl;
}

ValueArray::ValueArray()
    : ValueArray(100)
{
}

ValueArray::~ValueArray()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

ValueObject non_c_function_object()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    return {100};
}

ValueArray non_c_function_array()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    return {200};
}

Freyr::Freyr()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

Freyr::~Freyr()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

void Freyr::foo(int x)
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << x << std::endl;
}

Freki::Freki()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

Freki::~Freki()
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
}

// if Freyr* is used, Freyr should allow_raw_pointer
// using unique_ptr seems to be confusing.
// calling delete() in js side seems to not "break"
// even if it is already deleted here.
void Freki::foo(Freyr& f)
{
    f.foo(100);
}

void Freki::fizz(ValueObject& v)
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << v.x << std::endl;
}

void Freki::fuzz(ValueArray& v)
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << v.x << std::endl;
}
