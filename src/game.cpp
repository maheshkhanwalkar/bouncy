#include "game.h"
#include "event.h"
#include "sdl.h"

#include <SDL3/SDL_timer.h>

static bool should_quit(const std::vector<GameEvent>& events);

void update(Uint64 delta_time) {
    // TODO
}

void render(const SDLEnv& env) {
    // TODO
}

void game_loop(const SDLEnv &env) {
    Uint64 prev_time = 0;

    while (true) {
        std::vector<GameEvent> events = process_events();
        if (should_quit(events)) {
            break;
        }

        const Uint64 curr_time = SDL_GetTicks();
        const Uint64 delta_time = curr_time - prev_time;
        prev_time = curr_time;

        update(delta_time);
        render(env);
    }
}

bool should_quit(const std::vector<GameEvent>& events) {
    if (!events.empty() && events.back() == GameEvent::QUIT) {
        return true;
    }
    return false;
}
