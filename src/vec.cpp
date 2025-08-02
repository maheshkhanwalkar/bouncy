#include "vec.h"

vec2 vec2::operator*(const float &scalar) const {
    return vec2(this->x * scalar, this->y * scalar);
}

vec2 vec2::operator+(const vec2 &other) const {
    return vec2(this->x + other.x, this->y + other.y);
}

vec2 vec2::operator-(const vec2 &other) const {
    return vec2(this->x - other.x, this->y - other.y);
}
