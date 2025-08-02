#ifndef WALL_H
#define WALL_H

#include "vec.h"

// Ax + By + C = 0
struct line {
    float A;
    float B;
    float C;
};

class wall {
public:
    wall(vec2 pos, vec2 direction);
    [[nodiscard]] vec2 get_pos() const;
    [[nodiscard]] vec2 get_direction() const;
    [[nodiscard]] line get_line() const;
    [[nodiscard]] vec2 get_normal() const;
private:
    vec2 pos;
    vec2 direction;
    line line{};
};

#endif
