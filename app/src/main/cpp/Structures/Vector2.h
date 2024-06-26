//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_VECTOR2_H
#define ARKANOID_VECTOR2_H
#include <math.h>
struct Vector2 {
    float x;
    float y;

    Vector2(float xVal = 0.0f, float yVal = 0.0f);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    Vector2 operator-() const;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    static Vector2 zero();

    float Magnitude();
};

#endif //ARKANOID_VECTOR2_H
