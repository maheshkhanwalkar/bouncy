#include "game.h"
#include "event.h"

bool should_quit(const std::vector<GameEvent>& events);

void game_loop() {
    while (true) {
        std::vector<GameEvent> events = process_events();
        if (should_quit(events)) {
            break;
        }
    }
}

bool should_quit(const std::vector<GameEvent>& events) {
    if (!events.empty() && events.back() == GameEvent::QUIT) {
        return true;
    }
    return false;
}
