//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMEMANAGER_H
#define ARKANOID_GAMEMANAGER_H

#include "GameSceneObject.h"

class GameManager : public GameSceneObject {
    private:
        int _score;
    protected:
        void FixedUpdate() override;
    public:
        GameManager(JavaCppAdapter* adapter);
};


#endif //ARKANOID_GAMEMANAGER_H
