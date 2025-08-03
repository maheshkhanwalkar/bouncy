#ifndef VEC_H
#define VEC_H

#include <iostream>

struct vec2 {
    float x, y;

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(const float& scalar) const;
    vec2 operator/(const float& scalar) const;

    /**
     * Compute the dot product between two vectors.
     * @param other the other vector
     * @return the dot product
     */
    [[nodiscard]] float dot(const vec2& other) const;

    /**
     * Distance between two points.
     * @param other the other point
     * @return the Euclidean distance
     */
    [[nodiscard]] float dist(const vec2& other) const;

    /**
     * Vector length
     * @return this vector's length
     */
    [[nodiscard]] float length() const;

    /**
     * Normalized vector
     * @return the normalized (length 1) version of this vector
     */
    [[nodiscard]] vec2 normalize() const;

    /**
     * Print out vector (<x, y>)
     * @param os ostream to print to
     * @param vec vector to print
     * @return the passed in ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const vec2& vec);
};

vec2 operator*(const float& scalar, const vec2& vec);

#endif //VEC_H
