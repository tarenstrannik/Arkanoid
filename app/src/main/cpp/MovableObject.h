//
// Created by taren on 24.03.2024.
//

#ifndef ARKANOID_MOVABLEOBJECT_H
#define ARKANOID_MOVABLEOBJECT_H

#include "GameSceneObject.h"
#include "Structures/Vector2.h"

class MovableObject{
    protected:
        Vector2 _fieldSize;
        Vector2 _velocity;
        float _deltaTime;

    public:
        MovableObject(
                      Vector2 fieldSize=Vector2(0,0),
                      Vector2 velocity =Vector2(0,0),
                      float deltaTime=1);
        virtual Vector2 GetVelocity();
        virtual void SetVelocity(Vector2 velocity);
};


#endif //ARKANOID_MOVABLEOBJECT_H
