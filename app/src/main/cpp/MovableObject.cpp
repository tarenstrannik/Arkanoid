//
// Created by taren on 24.03.2024.
//

#include "MovableObject.h"

MovableObject::MovableObject(
               Vector2 fieldSize,
               Vector2 velocity,
               float deltaTime
               )
{
    _fieldSize=fieldSize;
    _velocity=velocity;
    _deltaTime=deltaTime;
}

Vector2 MovableObject::GetVelocity() {
    return _velocity;
}

void MovableObject::SetVelocity(Vector2 velocity) {
    _velocity=velocity;
}

