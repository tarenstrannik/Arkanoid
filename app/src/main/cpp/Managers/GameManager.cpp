//
// Created by taren on 23.03.2024.
//

#include "GameManager.h"

#include "../Structures/Color.h"
#include "../ScreenObjects/Player.h"
#include "../ScreenObjects/Ball.h"
#include "BrickFactory.h"
#include "UIManager.h"

GameManager::GameManager(JavaCppAdapter* adapter, Vector2 fieldSize, float deltaTime) : GameSceneObject(adapter)
{
    _lastId=0;
    _startPlayerLives=_playerLives;
    _gameObjectsToCollideWith={};
    _fieldSize=fieldSize;
    _deltaTime=deltaTime;
    OnRoundLoss=GenericEvent<int>();
    OnUpdateScore=GenericEvent<int>();
    OnFigureCollisionCheck= GenericEvent<Figure*>();
    OnNewRound = GenericEvent<>();

    _javaCppAdapter->OnRestartGame.Subscribe([this]() {
        RestartGame();
    });

    CreateUIManager();
    CreatePlayer();
    CreateBall();
    CreateBrickFactory();
}
void GameManager::FixedUpdate()
{
    GameSceneObject::FixedUpdate();

    if(_gameObjectsToCollideWith.size()==1)
    {
        OnNewRound.Invoke();
        return;
    }

    for (auto figure : _gameObjectsToCollideWith)
    {
        OnFigureCollisionCheck.Invoke(figure);
    }
}
void GameManager::CreatePlayer()
{
    auto playerID=CreateObjectId();
    auto playerShape = Shapes::RECTANGLE;
    auto playerXSize=_fieldSize.x*_playerWidthFraction;
    auto playerYSize = playerXSize/_playerWidthToHeight;
    auto playerX = _fieldSize.x*_playerStartPositionX;
    auto playerY = _fieldSize.y*_playerStartPositionY;
    auto playerVelocity = Vector2(0,0);
    _player = new Player(_javaCppAdapter, this,playerID,playerShape,
                   Vector2(playerX,playerY),Vector2(playerXSize,playerYSize),
                   _playerColor,true,_fieldSize, Vector2(playerX,playerY),
                   Vector2(0,0),_deltaTime);
    _gameObjectsToCollideWith.push_back(dynamic_cast<Figure*>(_player));
}
void GameManager::CreateBall()
{
    auto ballID=CreateObjectId();
    auto ballShape = Shapes::CIRCLE;
    auto ballXSize=_fieldSize.x*_ballWidthFraction;
    auto ballYSize = ballXSize;
    auto ballX = _fieldSize.x*_ballStartPositionX;
    auto ballY = _fieldSize.y*_ballStartPositionY;
    auto ballVelocity = Vector2(0,0);
    _ball = new Ball(_javaCppAdapter,this,ballID,ballShape,
                     Vector2(ballX,ballY),Vector2(ballXSize,ballYSize),
                     _ballColor,false,_fieldSize,
                     Vector2(0,0),_ballStartVelocityMagnitude,_ballSpeedIncrement,_deltaTime);
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

    if(_playerLives<=0)
    {
        GameOver();
    }
}

void GameManager::CreateBrickFactory() {
    _brickFactory=new BrickFactory(_javaCppAdapter,this,_fieldSize,
                                   _rows,_columns);
    _brickFactory->OnFigureCreation.Subscribe([this](Figure* figure) {

        _gameObjectsToCollideWith.push_back(figure);
        if(Brick* brick = dynamic_cast<Brick*>(figure))
        {
            brick->OnDestroy.Subscribe([this](Figure* figure) {
                _gameObjectsToCollideWith.remove(figure);
            });
            brick->OnCollision.Subscribe([this](int count) {
                _playerScore += count;
                OnUpdateScore.Invoke(_playerScore);
            });
        };
    });


}

void GameManager::GameOver() {
    _javaCppAdapter->GameOver(_playerScore);
}

void GameManager::CreateUIManager() {
    _uiManager=new UIManager(_javaCppAdapter,this,_playerLives,_playerScore);
}

void GameManager::RestartGame() {
    _playerScore=0;
    _playerLives=_startPlayerLives;
    OnNewRound.Invoke();
}
