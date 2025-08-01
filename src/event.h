#ifndef EVENT_H
#define EVENT_H

#include <vector>

enum class GameEvent {
    QUIT,
    NONE
};

/**
 * Process pending events.
 */
std::vector<GameEvent> process_events();

#endif //EVENT_H
