//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMESCENEOBJECT_H
#define ARKANOID_GAMESCENEOBJECT_H
#include "../Managers/JavaCppAdapter.h"

class GameSceneObject{
    using CallbackID = std::size_t;
    public:
        GameSceneObject(JavaCppAdapter* adapter);
        ~GameSceneObject();
    protected:
        JavaCppAdapter* _javaCppAdapter;
        virtual void FixedUpdate();
        CallbackID _fixedUpdate;
};


#endif //ARKANOID_GAMESCENEOBJECT_H
