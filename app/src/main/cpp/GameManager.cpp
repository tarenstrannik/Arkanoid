//
// Created by taren on 23.03.2024.
//

#include "GameManager.h"
#include "Structures/Color.h"
#include "Player.h"

GameManager::GameManager(JavaCppAdapter* adapter, Vector2 fieldSize) : GameSceneObject(adapter)
{
    _fieldSize=fieldSize;
    CreatePlayer();
}
void GameManager::FixedUpdate()
{
    GameSceneObject::FixedUpdate();

    _javaCppAdapter->UpdateScore(_fieldSize.x);
}
void GameManager::CreatePlayer()
{
    auto playerID=1;
    auto playerShape = Shapes::RECTANGLE;
    auto playerXSize=_fieldSize.x/5;
    auto playerYSize = playerXSize/7;
    auto playerX = _fieldSize.x/2;
    auto playerY = _fieldSize.y*0.9f;
    auto playerColor = Color(100,100,0);
    auto playerVelocity = Vector2(0,0);
    _player = new Player(_javaCppAdapter,playerID,playerShape,
                   Vector2(playerX,playerY),Vector2(playerXSize,playerYSize),
                   playerColor,true,_fieldSize);
}