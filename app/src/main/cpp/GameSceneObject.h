//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMESCENEOBJECT_H
#define ARKANOID_GAMESCENEOBJECT_H
#include "JavaCppAdapter.h"

class GameSceneObject{
    public:
        GameSceneObject(JavaCppAdapter* adapter);
        ~GameSceneObject();
    protected:
        JavaCppAdapter* _javaCppAdapter;
        virtual void FixedUpdate();
};


#endif //ARKANOID_GAMESCENEOBJECT_H
