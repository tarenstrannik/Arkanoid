//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMEMANAGER_H
#define ARKANOID_GAMEMANAGER_H
#include <list>
#include "GameSceneObject.h"
#include "Structures/Vector2.h"
#include "Enums/Shapes.h"


#include "UIManager.h"
#include "Figure.h"

class UIManager;
class Player;
class Brick;
class Ball;
class GameManager : public GameSceneObject {
    private:
        Vector2 _fieldSize;
        float _deltaTime;
        int _lastId;
        int _playerLives;
        int _playerScore;
        UIManager* _uiManager;
        std::list<Figure*> _gameObjectsToCollideWith;
        int CreateObjectId();
        Player* _player;
        void CreatePlayer();
        Ball* _ball;
        void CreateBall();
    protected:
        void FixedUpdate() override;
    public:
        GameManager(JavaCppAdapter* adapter, Vector2 fieldSize, float deltaTime);
        GenericEvent<int> OnRoundLoss;
        GenericEvent<int> OnUpdateScore;
        GenericEvent<Figure*> OnFigureCollision;
    void PlayerLoss();
};


#endif //ARKANOID_GAMEMANAGER_H
