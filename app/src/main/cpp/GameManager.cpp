//
// Created by taren on 23.03.2024.
//

#include "GameManager.h"
#include "Structures/Color.h"
#include "Player.h"

GameManager::GameManager(JavaCppAdapter* adapter, Vector2 fieldSize, float deltaTime) : GameSceneObject(adapter)
{
    _lastId=0;
    _gameObjectsToCollideWith={};
    _fieldSize=fieldSize;
    _deltaTime=deltaTime;
    CreatePlayer();
    CreateBall();
    _playerLives = 3;
    _playerScore = 0;
}
void GameManager::FixedUpdate()
{
    GameSceneObject::FixedUpdate();

    _javaCppAdapter->UpdateScore(_fieldSize.x);
}
void GameManager::CreatePlayer()
{
    auto playerID=CreateObjectId();
    auto playerShape = Shapes::RECTANGLE;
    auto playerXSize=_fieldSize.x/5;
    auto playerYSize = playerXSize/7;
    auto playerX = _fieldSize.x/2;
    auto playerY = _fieldSize.y*0.9f;
    auto playerColor = Color(100,100,0);
    auto playerVelocity = Vector2(0,0);
    _player = new Player(_javaCppAdapter,playerID,playerShape,
                   Vector2(playerX,playerY),Vector2(playerXSize,playerYSize),
                   playerColor,true,_fieldSize, Vector2(playerX,playerY),
                   Vector2(0,0),_deltaTime);
}
void GameManager::CreateBall()
{
    auto ballID=CreateObjectId();
    auto ballShape = Shapes::CIRCLE;
    auto ballXSize=_fieldSize.x/15;
    auto ballYSize = ballXSize;
    auto ballX = _fieldSize.x/2;
    auto ballY = _fieldSize.y*0.8f;
    auto ballColor = Color(0,100,255);
    auto ballVelocity = Vector2(0,0);
    _ball = new Ball(_javaCppAdapter,ballID,ballShape,
                     Vector2(ballX,ballY),Vector2(ballXSize,ballYSize),
                     ballColor,false,_fieldSize,
                     Vector2(0,0),_deltaTime);
    _ball->LossEvent.Subscribe([this]() {
        PlayerLoss();
    });
}

int GameManager::CreateObjectId()
{
    return ++_lastId;
}

void GameManager::PlayerLoss()
{
    _playerLives--;
    LossEvent.Invoke(_playerLives);
}
