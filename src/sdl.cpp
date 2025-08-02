#include "sdl.h"

#include <SDL3/SDL.h>
#include <stdexcept>

SDLEnv::SDLEnv(const std::string& window_name) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    this->window = SDL_CreateWindow(window_name.c_str(), 900, 900, 0);
    this->renderer = SDL_CreateRenderer(window, nullptr);
}

SDLEnv::~SDLEnv() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
