#include "event.h"
#include "sdl.h"

#include <SDL3/SDL_events.h>

std::vector<GameEvent> process_events() {
    std::vector<GameEvent> events;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE || event.type == SDL_EVENT_QUIT) {
            // there's no point retaining other events -- quit will override all
            events.clear();
            events.push_back(GameEvent::QUIT);
            break;
        }
    }

    return events;
}
