//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMEMANAGER_H
#define ARKANOID_GAMEMANAGER_H

#include "GameSceneObject.h"
#include "Structures/Vector2.h"
#include "Enums/Shapes.h"
#include "Player.h"

class GameManager : public GameSceneObject {
    private:
        Vector2 _fieldSize;
        Player* _player;
        void CreatePlayer();
    protected:
        void FixedUpdate() override;
    public:
        GameManager(JavaCppAdapter* adapter, Vector2 fieldSize);
};


#endif //ARKANOID_GAMEMANAGER_H
