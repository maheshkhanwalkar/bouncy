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

    /**
     * Wall's (starting) position
     * @return the position
     */
    [[nodiscard]] vec2 get_pos() const;

    /**
     * Wall's direction vector, which can be used to
     * compute the ending position of the wall.
     *
     * @return the direction vector
     */
    [[nodiscard]] vec2 get_direction() const;

    /**
     * Get the line representation of the wall
     * @return line representation
     */
    [[nodiscard]] line get_line() const;

    /**
     * Normal vector of the wall -- a vector which is
     * perpendicular to the wall.
     *
     * @return a normal vector
     */
    [[nodiscard]] vec2 get_normal() const;
private:
    vec2 pos;
    vec2 direction;
    line line{};
};

#endif
