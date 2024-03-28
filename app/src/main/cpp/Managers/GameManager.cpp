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
    _parameters=new Parameters();
    _playerLives = _parameters->_playerLives;
    _playerScore = _parameters->_playerScore;
    _gameObjectsToCollideWith={};
    _fieldSize=fieldSize;
    _deltaTime=deltaTime;
    OnRoundLoss=GenericEvent<int>();
    OnUpdateScore=GenericEvent<int>();
    OnNewRound = GenericEvent<>();
    OnGameOver = GenericEvent<>();

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
    if(_isGameOver)
        return;
    if(_player== nullptr && _ball== nullptr)
        return;
    if(!_isGameOver && _gameObjectsToCollideWith.size()==1)
    {
        OnNewRound.Invoke();
        return;
    }
    bool isCollision=false;
    std::list<Figure*> checkObjects(_gameObjectsToCollideWith.begin(), _gameObjectsToCollideWith.end());
    for (auto figure : checkObjects)
    {
        if(isCollision||_isGameOver)
            return;
        isCollision=_ball->CheckCollision(figure);
    }
}
void GameManager::CreateUIManager() {
    _uiManager=new UIManager(_javaCppAdapter,this,_parameters);
}
void GameManager::CreatePlayer()
{
    auto playerID=CreateObjectId();
    auto playerXSize=_fieldSize.x*_parameters->_playerWidthFraction;
    auto playerYSize = playerXSize/_parameters->_playerWidthToHeight;
    auto playerX = _fieldSize.x*_parameters->_playerStartPositionX;
    auto playerY = _fieldSize.y*_parameters->_playerStartPositionY;

    _player = new Player(_javaCppAdapter, this,_parameters,playerID,
                   Vector2(playerX,playerY),Vector2(playerXSize,playerYSize),
                   &_fieldSize,_deltaTime);
    _gameObjectsToCollideWith.push_back(dynamic_cast<Figure*>(_player));
}
void GameManager::CreateBall()
{
    auto ballID=CreateObjectId();
    auto ballXSize=_fieldSize.x*_parameters->_ballWidthFraction;
    auto ballYSize = ballXSize;
    auto ballX = _fieldSize.x*_parameters->_ballStartPositionX;
    auto ballY = _fieldSize.y*_parameters->_ballStartPositionY;

    _ball = new Ball(_javaCppAdapter,this,_parameters,ballID,
                     Vector2(ballX,ballY),Vector2(ballXSize,ballYSize),
                     &_fieldSize, _deltaTime);
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
    _brickFactory=new BrickFactory(_javaCppAdapter,this,_parameters,&_fieldSize);
    _brickFactory->OnBrickCreation.Subscribe([this](Figure* figure) {
        _gameObjectsToCollideWith.push_back(figure);
        if(Brick* brick = dynamic_cast<Brick*>(figure))
        {
            brick->OnDeactivation.Subscribe([this](Figure* figure) {
                _gameObjectsToCollideWith.erase(std::remove(_gameObjectsToCollideWith.begin(),
                                                            _gameObjectsToCollideWith.end(),
                                                            figure), _gameObjectsToCollideWith.end());
            });
            brick->OnCollision.Subscribe([this](int count) {
                _playerScore += count;
                OnUpdateScore.Invoke(_playerScore);
            });
        };
    });
}

void GameManager::GameOver() {
    _isGameOver=true;
    OnGameOver.Invoke();
    _javaCppAdapter->GameOver(_playerScore);
}

void GameManager::RestartGame() {
    _isGameOver=false;
    _playerScore=0;
    _playerLives=_parameters->_playerLives;
    _uiManager->ResetUI();
    OnNewRound.Invoke();
}
