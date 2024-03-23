//
// Created by taren on 23.03.2024.
//

#include "GameManager.h"
GameManager::GameManager(JavaCppAdapter* adapter) : GameSceneObject(adapter)
{
    _score=0;
}
void GameManager::FixedUpdate()
{
    GameSceneObject::FixedUpdate();
    _score++;
    _javaCppAdapter->UpdateScore(_score);
}