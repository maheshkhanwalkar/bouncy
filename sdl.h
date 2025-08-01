#ifndef SDL_ENV_H
#define SDL_ENV_H

#include <string>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

/**
 * SDL environment
 */
class SDLEnv {
public:
    explicit SDLEnv(const std::string &window_name);
    ~SDLEnv();

private:
    SDL_Window* window;
    SDL_Renderer *renderer;
};

#endif //SDL_ENV_H
