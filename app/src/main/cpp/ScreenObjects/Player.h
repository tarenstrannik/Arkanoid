//
// Created by taren on 24.03.2024.
//

#ifndef ARKANOID_PLAYER_H
#define ARKANOID_PLAYER_H

#include "../BaseClasses/Figure.h"
#include "../BaseClasses/MovableObject.h"
#include "../Parameters.h"

class GameManager;
class Player: public Figure, public MovableObject {
private:
    using CallbackID = std::size_t;
    CallbackID _setPosition;
    Vector2 _prevPosition;
    void UpdateVelocity();
    GameManager* _gameManager;
    void ResetPosition(int value);
    float _topBorder;
    float _bottomBorder;
protected:
    void FixedUpdate() override;
    void SetPosition(Vector2 position) override;
    void ConstraintRestrictions() override;

public:
    Player(
            JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id, Vector2 position, Vector2 size,
            Vector2* fieldSize, float deltaTime);
    ~Player();
    float GetTopBorder() override;
    float GetBottomBorder() override;
};


#endif //ARKANOID_PLAYER_H
