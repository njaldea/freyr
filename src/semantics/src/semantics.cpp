#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>

#include <unordered_map>

#include <memory>

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

// value array/object should be as small as possible
// - when received by a method, a copy is created
// - when returned by a method, a copy is created
// I think the object, once forwarded to JS space
// it is automatically converted to a JS object instance
// thus, to be "read" by c++, it is necessary to be converted
// back to C++ instance.

struct ValueObject
{
    int x;

    ValueObject(int _x)
        : x(_x)
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }

    ValueObject()
        : ValueObject(100)
    {
    }

    ~ValueObject()
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }
};

struct ValueArray
{
    int x;

    ValueArray(int _x)
        : x(_x)
    {
        std::cout << __FILE__ //
                  << ":"      //
                  << __LINE__ //
                  << ":"      //
                  << __FUNCTION__ << std::endl;
    }

    ValueArray()
        : ValueArray(100)
    {
    }

    ~ValueArray()
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }
};

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

class Freyr
{
public:
    Freyr()
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }

    ~Freyr()
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }

    void foo(int x)
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << x << std::endl;
    }
};

class Freki
{
public:
    Freki()
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }

    ~Freki()
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    }

    // if Freyr* is used, Freyr should allow_raw_pointer
    // using unique_ptr seems to be confusing.
    // calling delete() in js side seems to not "break"
    // even if it is already deleted here.
    void foo(Freyr& f)
    {
        f.foo(100);
    }

    void fizz(ValueObject& v)
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << v.x << std::endl;
    }

    void fuzz(ValueArray& v)
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ":" << v.x << std::endl;
    }
};

EMSCRIPTEN_BINDINGS()
{
    emscripten::value_object<ValueObject>("ValueStruct_value_object").field("x", &ValueObject::x);

    emscripten::value_array<ValueArray>("ValueStruct_value_array").element(&ValueArray::x);

    emscripten::class_<Freyr>("Freyr") //
        .constructor()                 //
        .function("foo", &Freyr::foo);

    emscripten::class_<Freki>("Freki")
        .constructor()
        .function("foo", &Freki::foo)
        .function("fizz", &Freki::fizz)
        .function("fuzz", &Freki::fuzz);

    emscripten::function("non_c_function_array", &non_c_function_array);
    emscripten::function("non_c_function_object", &non_c_function_object);
}

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent* e, void* userData)
{
    std::cout              //
        << __FILE__ << ":" //
        << __LINE__ << ":" //
        << __FUNCTION__ << std::endl;
    std::cout                  //
        << eventType << ':'    //
        << e->movementX << ':' //
        << e->movementY << std::endl;
    return false;
}

int main()
{
    const auto isBrowser = EM_ASM_INT({ return typeof window == "object" ? 1 : 0; });
    if (isBrowser)
    {
        emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, mouse_callback);
    }
}
