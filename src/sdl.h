#ifndef SDL_ENV_H
#define SDL_ENV_H

#include <string>
#include <unordered_map>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

/**
 * SDL environment
 */
class SDLEnv {
public:
    explicit SDLEnv(const std::string &window_name);
    ~SDLEnv();

    SDL_Texture* get_texture(const std::string &name);
    void load_texture(const std::string &path, const std::string &name);

    SDL_Window* window;
    SDL_Renderer *renderer;
    std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif //SDL_ENV_H
