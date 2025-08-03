#include "event.h"
#include "sdl.h"

#include <SDL3/SDL_events.h>

static void handle_quit(std::vector<GameEvent>& events) {
    // there's no point retaining other events -- quit will override all
    events.clear();
    events.push_back(GameEvent::QUIT);
}

static void handle_key_event(std::vector<GameEvent>& events, const SDL_Event& event) {
    switch (event.key.key) {
        case SDLK_ESCAPE:
            handle_quit(events);
            break;
        case SDLK_EQUALS:
            // + key (SHIFT and EQUALS)
            if ((event.key.mod & SDL_KMOD_SHIFT) != 0) {
                events.push_back(GameEvent::INCREASE_BALLS);
            }
            break;
        case SDLK_MINUS:
            events.push_back(GameEvent::DECREASE_BALLS);
            break;
        default:
            break;
    }
}

std::vector<GameEvent> process_events() {
    std::vector<GameEvent> events;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_KEY_DOWN:
                handle_key_event(events, event);
                break;
            case SDL_EVENT_QUIT:
                handle_quit(events);
                break;
            default:
                break;
        }

        if (!events.empty() && events.back() == GameEvent::QUIT) {
            break;
        }
    }

    return events;
}
