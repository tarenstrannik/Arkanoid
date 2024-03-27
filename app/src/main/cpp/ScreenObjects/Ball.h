//
// Created by taren on 25.03.2024.
//

#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H
#include "../BaseClasses/Figure.h"
#include "Brick.h"
#include "Player.h"
#include "../BaseClasses/MovableObject.h"

class GameManager;
class Ball: public Figure, public MovableObject {
private:
    using CallbackID = std::size_t;
    GameManager* _gameManager;
    void Move();
    bool IsCollisionWithWalls();
    bool IsCollisionWithCeiling();
    bool IsCollisionWithFloor();
    CallbackID _startMovement;
    void CheckCollision(Figure *Figure);

protected:
    Parameters* _parameters;
    void FixedUpdate() override;
    void ConstraintRestrictions() override;
public:
    Ball(
            JavaCppAdapter *adapter, GameManager* gameManager, Parameters* parameters, int id, Vector2 position, Vector2 size,
            Vector2* fieldSize, float deltaTime);
    ~Ball();
    void StartMovement();
    GenericEvent<> OnLoss;
    void ResetBall(int value);


};


#endif //ARKANOID_BALL_H
