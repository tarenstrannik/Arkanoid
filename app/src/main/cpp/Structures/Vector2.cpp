//
// Created by taren on 23.03.2024.
//

#include "Vector2.h"

Vector2::Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}
Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}