#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <emscripten.h>
#include <emscripten/bind.h>

#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Rect rect = {.x = 10, .y = 10, .w = 150, .h = 100};

void redraw()
{
    SDL_SetRenderDrawColor(renderer, /* RGBA: black */ 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, /* RGBA: green */ 0x00, 0x80, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

std::array buttons = {false, false, false, false};

void handle_button(SDL_Keycode code, bool value)
{
    switch (code)
    {
    case SDLK_UP:
        buttons[0] = value;
        break;
    case SDLK_DOWN:
        buttons[1] = value;
        break;
    case SDLK_RIGHT:
        buttons[2] = value;
        break;
    case SDLK_LEFT:
        buttons[3] = value;
        break;
    }
}

bool handle_events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        return false;
    }
    if (event.type == SDL_KEYDOWN)
    {
        handle_button(event.key.keysym.sym, true);
    }
    else if (event.type == SDL_KEYUP)
    {
        handle_button(event.key.keysym.sym, false);
    }

    const auto mod = [&](bool inc, bool dcr, int SDL_Rect::*prop)
    {
        if (inc && dcr)
        {
            return false;
        }
        if (inc)
        {
            rect.*prop += 1;
        }
        else if (dcr)
        {
            rect.*prop -= 1;
        }
        return true;
    };
    if (mod(buttons[1], buttons[0], &SDL_Rect::y) | mod(buttons[2], buttons[3], &SDL_Rect::x))
    {
        redraw();
    }
    return true;
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(300, 300, 0, &window, &renderer);
    redraw();
    emscripten_set_main_loop([]() { handle_events(); }, 0, true);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
