#ifndef VEC_H
#define VEC_H

struct vec2 {
    float x, y;

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(const float& scalar) const;
    vec2 operator/(const float& scalar) const;

    [[nodiscard]] float dot(const vec2& other) const;

    [[nodiscard]] float dist(const vec2& other) const;
    [[nodiscard]] float length() const;
    [[nodiscard]] vec2 normalize() const;
};

vec2 operator*(const float& scalar, const vec2& vec);

#endif //VEC_H
