#include "event.h"
#include "sdl.h"

#include <SDL3/SDL_events.h>

void game_loop(SDLEnv& env) {
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
            quit = true;
        }
    }
}
