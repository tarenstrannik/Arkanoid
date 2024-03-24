//
// Created by taren on 24.03.2024.
//

#include "MovableObject.h"

MovableObject::MovableObject(
               Vector2 position,
               Vector2 prevPosition,
               float deltaTime
               )
{
    _position=position;
    _prevPosition=position;
    _deltaTime=deltaTime;
}

