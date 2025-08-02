#ifndef BALL_H
#define BALL_H
#include "vec.h"

class ball {
public:
    /**
     * Construct a ball
     * @param pos ball's starting position
     * @param velocity ball's velocity in m/s
     */
    ball(vec2 pos, vec2 velocity);

    /**
     * Get the ball's position
     * @return the current position
     */
    vec2 get_pos() const;

    /**
     * Move the ball
     * @param time elapsed time (in seconds)
     */
    void move(float time);

private:
    vec2 pos;
    vec2 velocity;
};

#endif //BALL_H
