//
// Created by taren on 23.03.2024.
//

#include "GameSceneObject.h"

GameSceneObject::GameSceneObject(JavaCppAdapter* adapter)
{
    _javaCppAdapter = adapter;

    _javaCppAdapter->FixedUpdateEvent.Subscribe([this]() {
        FixedUpdate();
    });
}
GameSceneObject::~GameSceneObject() {
    _javaCppAdapter->FixedUpdateEvent.Unsubscribe([this]() {
        FixedUpdate();
    });
};
void GameSceneObject::FixedUpdate()
{

}




