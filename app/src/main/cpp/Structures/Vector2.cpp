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

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2& Vector2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2 Vector2::zero() {
    return {0,0};
}
float Vector2::Magnitude()
{
    return sqrtf(x * x + y * y);
};
