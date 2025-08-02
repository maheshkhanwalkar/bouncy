#include "ball.h"

ball::ball(const vec2 pos, const vec2 velocity): pos(pos), velocity(velocity) { }

vec2 ball::get_pos() const {
    return this->pos;
}

void ball::move(const float time) {
    // s = s_0 + v * t
    this->pos = this->pos + this->velocity * time;
}
