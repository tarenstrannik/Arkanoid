//
// Created by taren on 24.03.2024.
//

#ifndef ARKANOID_PLAYER_H
#define ARKANOID_PLAYER_H

#include "Figure.h"
#include "MovableObject.h"
#include "GameManager.h"

class GameManager;
class Player: public Figure, public MovableObject {
private:
    using CallbackID = std::size_t;
    CallbackID _setPosition;
    Vector2 _prevPosition;
    void UpdateVelocity();
    GameManager* _gameManager;
    void ResetPosition(int value);
protected:
    void FixedUpdate() override;
    void SetPosition(Vector2 position) override;
    void ConstraintRestrictions() override;

public:
    Player(
           JavaCppAdapter* adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
           Color color, bool registerTouch, Vector2 fieldSize,Vector2 prevPosition, Vector2 velocity,float deltaTime);
    ~Player();
};


#endif //ARKANOID_PLAYER_H
