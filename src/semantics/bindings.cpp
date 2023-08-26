#include "semantics.hpp"

#include <emscripten/bind.h>
#include <emscripten/html5.h>

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
