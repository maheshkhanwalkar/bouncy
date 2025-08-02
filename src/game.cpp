#include "game.h"

#include <iostream>

#include "event.h"
#include "sdl.h"
#include "ball.h"

#include <SDL3/SDL_timer.h>
#include <vector>

static bool should_quit(const std::vector<GameEvent>& events);

struct game_state {
    std::vector<ball> balls;
    std::vector<wall> walls;
};

game_state init() {
    // The entire initial state is hardcoded for now
    const ball one = {vec2(100, 100), 10, 1, vec2(50, 80)};
    const ball two = {vec2(300, 200), 15, 3, vec2(-30, 100)};

    const wall top = {vec2(10, 10), vec2(400, 0)};
    const wall right = {vec2(410, 10), vec2(0, 400)};
    const wall bottom = {vec2(410, 410), vec2(-400, 0)};
    const wall left = {vec2(10, 410), vec2(0, -400)};

    return {std::vector{one, two}, std::vector{top, right, bottom, left}};
}

void update(game_state& state, const Uint64 delta_time_ms) {
    // Update the ball positions
    const float time_s = static_cast<float>(delta_time_ms) / 1000.0f;
    for (ball& ball : state.balls) {
        ball.move(time_s);
    }

    // Check for ball-wall collisions
    for (ball& ball : state.balls) {
        for (wall& wall : state.walls) {
            if (ball.is_colliding(wall)) {
                ball.collide(wall);
                ball.move(time_s);
            }
        }
    }

    // Check for ball-ball collisions
    for (int i = 0; i < state.balls.size(); i++) {
        for (int j = i + 1; j < state.balls.size(); j++) {
            ball& one = state.balls[i];
            ball& two = state.balls[j];

            if (one.is_colliding(two)) {
                one.collide(two);
                one.move(time_s);
                two.move(time_s);
            }
        }
    }
}

void render_wall(const SDLEnv& env, const wall& wall) {
    const float x1 = wall.get_pos().x;
    const float y1 = wall.get_pos().y;
    const float x2 = x1 + wall.get_direction().x;
    const float y2 = y1 + wall.get_direction().y;

    SDL_SetRenderDrawColor(env.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(env.renderer, x1, y1, x2, y2);
}

void render_ball(const SDLEnv& env, const ball& ball) {
    // FIXME: actually render a circle and not a rect
    const auto rect = SDL_FRect{ball.get_pos().x - ball.get_radius(),
        ball.get_pos().y - ball.get_radius(), ball.get_radius() * 2, ball.get_radius() * 2};

    SDL_SetRenderDrawColor(env.renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(env.renderer, &rect);
}

void render(const SDLEnv& env, const game_state& state) {
    SDL_SetRenderDrawColor(env.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(env.renderer);

    for (const wall& wall : state.walls) {
        render_wall(env, wall);
    }
    for (const ball& ball : state.balls) {
        render_ball(env, ball);
    }

    SDL_RenderPresent(env.renderer);
}

void game_loop(const SDLEnv &env) {
    Uint64 prev_time = 0;
    game_state state = init();

    while (true) {
        std::vector<GameEvent> events = process_events();
        if (should_quit(events)) {
            break;
        }

        const Uint64 curr_time = SDL_GetTicks();
        const Uint64 delta_time = curr_time - prev_time;
        prev_time = curr_time;

        update(state, delta_time);
        render(env, state);
    }
}

bool should_quit(const std::vector<GameEvent>& events) {
    if (!events.empty() && events.back() == GameEvent::QUIT) {
        return true;
    }
    return false;
}
