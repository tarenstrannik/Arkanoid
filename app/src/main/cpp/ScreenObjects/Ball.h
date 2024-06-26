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


protected:
    Parameters* _parameters;
    void FixedUpdate() override;
    void ConstraintPosition() override;
    Vector2 ConstraintVelocity(Vector2 velocity);
public:
    Ball(
            JavaCppAdapter *adapter, GameManager* gameManager, Parameters* parameters, int id, Vector2 position, Vector2 size,
            Vector2* fieldSize, float deltaTime);
    ~Ball();
    void StartMovement();
    GenericEvent<> OnLoss;
    void ResetBall(int value);
    bool CheckCollision(Figure *Figure);
};


#endif //ARKANOID_BALL_H
