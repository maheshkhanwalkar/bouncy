#include "vec.h"

#include <cmath>

vec2 vec2::operator*(const float &scalar) const {
    return vec2(this->x * scalar, this->y * scalar);
}

vec2 operator*(const float &scalar, const vec2 &vec) {
    return vec * scalar;
}

vec2 vec2::operator/(const float &scalar) const {
    return vec2(this->x / scalar, this->y / scalar);
}

vec2 vec2::operator+(const vec2 &other) const {
    return vec2(this->x + other.x, this->y + other.y);
}

vec2 vec2::operator-(const vec2 &other) const {
    return vec2(this->x - other.x, this->y - other.y);
}

float vec2::dot(const vec2 &other) const {
    return this->x * other.x + this->y * other.y;
}

float vec2::dist(const vec2 &other) const {
    // Euclidian distance: dist(this, other) = sqrt((this_x - other_x)^2 + (this_y - other_y)^2)
    return sqrtf(powf(this->x - other.x, 2) + powf(this->y - other.y, 2));
}

float vec2::length() const {
    return sqrtf(powf(this->x, 2) + powf(this->y, 2));
}

vec2 vec2::normalize() const {
    return *this / this->length();
}

std::ostream& operator<<(std::ostream& os, const vec2& vec) {
    os << "<" << vec.x << ", " << vec.y << ">";
    return os;
}
