#include "game.h"

#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>

#include <vector>

#include "ball.h"
#include "event.h"
#include "rand.h"
#include "sdl.h"

static constexpr float OFFSET = 10;
static constexpr int MAX_BALLS = 30;

struct game_state {
    std::vector<ball> balls;
    std::vector<wall> walls;
    random_generator rng;
};

static vec2 generate_random_velocity(random_generator& rng) {
    int x = rng.get(80, 100);
    int y = rng.get(80, 100);

    rng.get_bool() ? x *= -1 : 0;
    rng.get_bool() ? y *= -1 : 0;

    return vec2(static_cast<float>(x), static_cast<float>(y));
}

static SDL_Color get_sdl_color(const ball_color color) {
    switch (color) {
        case ball_color::RED:
            return {255, 0, 0, SDL_ALPHA_OPAQUE};
        case ball_color::GREEN:
            return {0, 255, 0, SDL_ALPHA_OPAQUE};
        case ball_color::BLUE:
            return {0, 0, 255, SDL_ALPHA_OPAQUE};
        case ball_color::YELLOW:
            return {255, 255, 0, SDL_ALPHA_OPAQUE};
        case ball_color::PURPLE:
            return {255, 0, 255, SDL_ALPHA_OPAQUE};
        case ball_color::ORANGE:
            return {255, 165, 0, SDL_ALPHA_OPAQUE};
    }

    throw std::runtime_error(std::format("invalid ball color: {}", static_cast<int>(color)));
}

static void create_ball(const SDLEnv& env, random_generator &rng, std::vector<ball>& balls) {
    int w, h;
    SDL_GetWindowSizeInPixels(env.window, &w, &h);

    while (true) {
        const float mass = rng.get(1.0f, 5.0f);
        const float radius = 10 * std::sqrt(mass);

        const float x = rng.get(OFFSET + radius * 2, w - OFFSET - radius * 2);
        const float y = rng.get(OFFSET + radius * 2, h - OFFSET - radius * 2);
        const auto velocity = generate_random_velocity(rng);

        const auto color = static_cast<ball_color>(rng.get(0, 5));
        const ball b = {vec2(x, y), radius, mass, velocity, color};

        // We don't want to add a ball already colliding with another ball
        bool is_colliding = false;
        for (const ball& other: balls) {
            if (b.is_colliding(other)) {
                is_colliding = true;
                break;
            }
        }

        if (!is_colliding) {
            balls.emplace_back(b);
            break;
        }
    }
}

static game_state init(SDLEnv& env) {
    int w, h;
    SDL_GetWindowSizeInPixels(env.window, &w, &h);

    // Load ball texture
    env.load_texture("assets/ball.png", "ball");

    // Generate walls
    const wall top = {vec2(OFFSET, OFFSET), vec2(w - 2 * OFFSET, 0)};
    const wall right = {vec2(w - OFFSET, OFFSET), vec2(0, h - 2 * OFFSET)};
    const wall bottom = {vec2(w - OFFSET, h - OFFSET), vec2(-w + 2 * OFFSET, 0)};
    const wall left = {vec2(10, h - OFFSET), vec2(0, -h + 2 * OFFSET)};
    const std::vector walls = {top, right, bottom, left};

    // Generate balls
    random_generator rng;

    const int num_balls = rng.get(10, MAX_BALLS);
    std::vector<ball> balls;

    for (int i = 0; i < num_balls; i++) {
        create_ball(env, rng, balls);
    }

    return {balls, walls, rng};
}

static bool handle_events(SDLEnv& env, game_state& state, const std::vector<GameEvent>& events) {
    for (const GameEvent& event : events) {
        switch (event) {
            case GameEvent::QUIT:
                return false;
            case GameEvent::INCREASE_BALLS:
                if (state.balls.size() == MAX_BALLS) {
                    break;
                }
                create_ball(env, state.rng, state.balls);
                break;
            case GameEvent::DECREASE_BALLS:
                state.balls.erase(state.balls.begin());
                break;
        }
    }

    return true;
}

static void update(game_state& state, const Uint64 delta_time_ms) {
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

static void render_wall(const SDLEnv& env, const wall& wall) {
    const float x1 = wall.get_pos().x;
    const float y1 = wall.get_pos().y;
    const float x2 = x1 + wall.get_direction().x;
    const float y2 = y1 + wall.get_direction().y;

    SDL_SetRenderDrawColor(env.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(env.renderer, x1, y1, x2, y2);
}

static void render_ball(SDLEnv& env, const ball& ball) {
    const auto rect = SDL_FRect{ball.get_pos().x - ball.get_radius(),
        ball.get_pos().y - ball.get_radius(), ball.get_radius() * 2, ball.get_radius() * 2};

    SDL_Texture* texture = env.get_texture("ball");
    const auto sdl_color = get_sdl_color(ball.get_color());

    SDL_SetTextureColorMod(texture, sdl_color.r, sdl_color.g, sdl_color.b);
    SDL_RenderTexture(env.renderer, texture, nullptr, &rect);
}

static void render(SDLEnv& env, const game_state& state) {
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

void game_loop(SDLEnv &env) {
    Uint64 prev_time = 0;
    game_state state = init(env);

    while (true) {
        if (std::vector<GameEvent> events = process_events();
            !handle_events(env, state, events)) {
            break;
        }

        const Uint64 curr_time = SDL_GetTicks();
        const Uint64 delta_time = curr_time - prev_time;
        prev_time = curr_time;

        update(state, delta_time);
        render(env, state);
    }
}
