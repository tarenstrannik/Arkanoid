//
// Created by taren on 23.03.2024.
//

#include "GameManager.h"

#include "Structures/Color.h"
#include "Player.h"
#include "Ball.h"

GameManager::GameManager(JavaCppAdapter* adapter, Vector2 fieldSize, float deltaTime) : GameSceneObject(adapter)
{
    _lastId=0;
    _gameObjectsToCollideWith={};
    _fieldSize=fieldSize;
    _deltaTime=deltaTime;

    _playerLives = 3;
    _playerScore = 0;
    _uiManager=new UIManager(_javaCppAdapter,this,_playerLives,_playerScore);

    CreatePlayer();
    CreateBall();

}
void GameManager::FixedUpdate()
{
    GameSceneObject::FixedUpdate();

    //перебираем все колл фигуры и вызываем событие ончекколижн
    for (auto figure : _gameObjectsToCollideWith) {
        // Вызов события OnFigureCollision для каждого элемента
        OnFigureCollision.Invoke(figure);
    }
    // на событие подписан болл, который проверяет для каждого коллизию
    //если коллихзия то изменение скорости (также с проверкой если плеер то плюсуем скорость плеера)
    // и затем проверка является ли наследником класса брик
    // если да то вызывает функцию в брик "коллайд"
    // коллайд вызывает событие брик коллайд (инт) на которое подписан гейм менеджер и выполняет обработку (уничтожает
    // блок или изменяет его и т.п.
    //при уничтожении вызывается событие он дестрой, на которое подписан гейм менеджер. он тогда удаляет брик из списка проверки коллизий

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
    _player = new Player(_javaCppAdapter, this,playerID,playerShape,
                   Vector2(playerX,playerY),Vector2(playerXSize,playerYSize),
                   playerColor,true,_fieldSize, Vector2(playerX,playerY),
                   Vector2(0,0),_deltaTime);
    _gameObjectsToCollideWith.push_back(dynamic_cast<Figure*>(_player));
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
    auto startVelocityMagnitude=300.0f;
    _ball = new Ball(_javaCppAdapter,this,ballID,ballShape,
                     Vector2(ballX,ballY),Vector2(ballXSize,ballYSize),
                     ballColor,false,_fieldSize,
                     Vector2(0,0),startVelocityMagnitude,_deltaTime);
    _ball->OnLoss.Subscribe([this]() {
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
    OnRoundLoss.Invoke(_playerLives);
}
