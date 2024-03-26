//
// Created by taren on 23.03.2024.
//

#include "GameSceneObject.h"

GameSceneObject::GameSceneObject(JavaCppAdapter* adapter)
{
    _javaCppAdapter = adapter;
    _fixedUpdate=_javaCppAdapter->OnFixedUpdate.Subscribe([this]() {
        FixedUpdate();
    });
}
GameSceneObject::~GameSceneObject() {
    _javaCppAdapter->OnFixedUpdate.Unsubscribe(_fixedUpdate);
};
void GameSceneObject::FixedUpdate()
{

}




