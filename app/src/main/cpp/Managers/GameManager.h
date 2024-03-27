//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMEMANAGER_H
#define ARKANOID_GAMEMANAGER_H
#include <list>
#include "../BaseClasses/GameSceneObject.h"
#include "../Structures/Vector2.h"
#include "../Enums/Shapes.h"
#include "../ScreenObjects/Brick.h"
#include "../Structures/Parameters.h"

class UIManager;
class Player;
class Ball;
class BrickFactory;

class GameManager : public GameSceneObject {
private:
    Vector2 _fieldSize;
    float _deltaTime;
    int _lastId;

    Parameters* _parameters;
    void CreateUIManager();
    UIManager *_uiManager;
    std::list<Figure *> _gameObjectsToCollideWith;
    Player *_player;
    int _playerLives;
    int _playerScore;
    void CreatePlayer();

    Ball *_ball;

    void CreateBall();

    BrickFactory *_brickFactory;
    void CreateBrickFactory();
    void GameOver();
    void RestartGame();

    bool _isGameOver=false;

protected:
    void FixedUpdate() override;

public:
    int CreateObjectId();

    GameManager(JavaCppAdapter *adapter, Vector2 fieldSize, float deltaTime);

    GenericEvent<int> OnRoundLoss;
    GenericEvent<int> OnUpdateScore;
    GenericEvent<Figure *> OnFigureCollisionCheck;

    void PlayerLoss();
    GenericEvent<> OnNewRound;
    GenericEvent<> OnGameOver;
};
#endif //ARKANOID_GAMEMANAGER_H
