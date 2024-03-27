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

class UIManager;
class Player;
class Ball;
class BrickFactory;

class GameManager : public GameSceneObject {
private:
    Vector2 _fieldSize;
    float _deltaTime;
    int _lastId;
    //playerparams
    float _playerWidthFraction = 0.2f;//from screen
    float _playerWidthToHeight = 7.0f;
    float _playerStartPositionX = 0.5f;//from screen width
    float _playerStartPositionY = 0.9f;//from screen height
    Color _playerColor = Color(100, 100, 0);
    int _playerLives = 1;
    int _startPlayerLives;
    int _playerScore = 0;

    //ball params
    float _ballWidthFraction = 0.06f;//from screen
    float _ballStartPositionX = 0.5f;//from screen width
    float _ballStartPositionY = 0.8f;//from screen height
    Color _ballColor = Color(0, 100, 255);
    float _ballStartVelocityMagnitude = 300.0f;
    float _ballSpeedIncrement = 1.1f;
    //briks factory params
    int _rows = 5;
    int _columns = 5;
    void CreateUIManager();
    UIManager *_uiManager;
    std::list<Figure *> _gameObjectsToCollideWith;
    Player *_player;

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
