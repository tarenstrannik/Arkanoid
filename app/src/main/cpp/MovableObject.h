//
// Created by taren on 24.03.2024.
//

#ifndef ARKANOID_MOVABLEOBJECT_H
#define ARKANOID_MOVABLEOBJECT_H

#include "GameSceneObject.h"
#include "Structures/Vector2.h"

class MovableObject{
    private:
        Vector2 _position;
        Vector2 _prevPosition;
        float _deltaTime;
    public:
        MovableObject(
                      Vector2 position=Vector2(0,0),
                      Vector2 prevPosition=Vector2(0,0),
                      float deltaTime=1);

};


#endif //ARKANOID_MOVABLEOBJECT_H
