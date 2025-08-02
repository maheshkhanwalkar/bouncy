#ifndef VEC_H
#define VEC_H

struct vec2 {
    float x, y;

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(const float& scalar) const;
};

#endif //VEC_H
