#include "ball.h"

ball::ball(const vec2 pos, const float radius, const float mass, const vec2 velocity): pos(pos), velocity(velocity),
    radius(radius), mass(mass) { }

void ball::move(const float time) {
    // s = s_0 + v * t
    this->pos = this->pos + this->velocity * time;
}

bool ball::is_colliding(const ball &other) const {
    // two balls are intersecting iff the distance between their centers is <=
    // the sum of their radii.
    return this->pos.dist(other.pos) <= this->radius + other.radius;
}

bool ball::is_colliding(const wall &wall) const {
    const line line = wall.get_line();
    const vec2 pos = this->pos;

    // Compute the distance from pos to line
    const float dist = std::abs(line.A * pos.x + line.B * pos.y + line.C) /
        vec2(line.A, line.B).length();

    return dist <= this->radius;
}

void ball::collide(const wall &wall) {
    if (!this->is_colliding(wall)) {
        return;
    }

    // Perfectly elastic collision against an immovable wall -- the ball's speed (magnitude)
    // is preserved, but the direction is reflected over the wall's normal vector.
    //   V = V_1 - 2 * (V_1 . n) n
    this->velocity = this->velocity - 2 * this->velocity.dot(wall.get_normal()) * wall.get_normal();
}

void ball::collide(ball &other) {
    if (!this->is_colliding(other)) {
        return;
    }

    // Perfectly elastic collision between the two balls
    const vec2 our_new_velocity = ((this->mass - other.mass) / (this->mass + other.mass)) * this->velocity +
        (2 * other.mass / (this->mass + other.mass)) * other.velocity;
    const vec2 other_new_velocity = (2 * this->mass / (this->mass + other.mass)) * this->velocity +
        ((other.mass - this->mass) / (this->mass + other.mass)) * other.velocity;

    this->velocity = our_new_velocity;
    other.velocity = other_new_velocity;
}

vec2 ball::get_pos() const {
    return this->pos;
}

float ball::get_radius() const {
    return this->radius;
}
