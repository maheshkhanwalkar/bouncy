#include "sdl.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdexcept>

SDLEnv::SDLEnv(const std::string& window_name) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL_Init failed");
    }

    this->window = SDL_CreateWindow(window_name.c_str(), 900, 900, 0);
    this->renderer = SDL_CreateRenderer(window, nullptr);
    this->textures = {};
}

SDLEnv::~SDLEnv() {
    for (const std::pair<std::string, SDL_Texture*> entries : this->textures) {
        SDL_DestroyTexture(entries.second);
    }
    this->textures.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* SDLEnv::get_texture(const std::string &name) {
    if (!this->textures.contains(name)) {
        return nullptr;
    }
    return this->textures[name];
}

void SDLEnv::load_texture(const std::string &path, const std::string &name) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_DestroySurface(surface);

    this->textures[name] = texture;
}
