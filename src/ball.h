#ifndef BALL_H
#define BALL_H

#include "vec.h"
#include "wall.h"

class ball {
public:
    /**
     * Construct a ball
     * @param pos ball's starting position
     * @param radius ball's radius (in meters)
     * @param mass the ball's mass (in kg)
     * @param velocity ball's velocity in m/s
     */
    ball(vec2 pos, float radius, float mass, vec2 velocity);

    /**
     * Move the ball
     * @param time elapsed time (in seconds)
     */
    void move(float time);

    /**
     * Are the two balls colliding?
     * @param other the other ball
     * @return true if they are colliding (intersecting)
     */
    [[nodiscard]] bool is_colliding(const ball &other) const;

    /**
     * Is the ball colliding with a wall?
     * @param wall the wall
     * @return true if they are colliding (intersecting)
     */
    [[nodiscard]] bool is_colliding(const wall &wall) const;

    /**
     * Collide the ball and wall
     * @param wall the wall
     */
    void collide(const wall &wall);

    /**
     * Collide the two balls together
     * @param other the other ball
     */
    void collide(ball &other);

    [[nodiscard]] vec2 get_pos() const;
    [[nodiscard]] float get_radius() const;
private:
    vec2 pos;
    vec2 velocity;
    float radius;
    float mass;
};

#endif //BALL_H
