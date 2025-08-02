#include "wall.h"

wall::wall(const vec2 pos, const vec2 direction): pos(pos), direction(direction) {
    const auto [x2, y2] = pos + direction;

    // Compute the Ax + By + C = 0 form
    const float A = pos.y - y2;
    const float B = x2 - pos.x;
    const float C = pos.x * y2 - pos.y * x2;

    this->line = ::line(A, B, C);
}

vec2 wall::get_pos() const {
    return this->pos;
}

vec2 wall::get_direction() const {
    return this->direction;
}

line wall::get_line() const {
    return this->line;
}

vec2 wall::get_normal() const {
    /*
     * There are two possible normal vectors; however, we opt
     * to just select one. Flipping the wall vector would get
     * you the other normal.
     *
     * V = Ai + Bj
     * N = (-Bi + Aj) / ||V||
     */
    const auto normal = vec2(-this->direction.y, this->direction.x);
    return normal.normalize();
}

