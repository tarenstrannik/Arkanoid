//
// Created by taren on 25.03.2024.
//

#ifndef ARKANOID_BALL_H
#define ARKANOID_BALL_H
#include "Figure.h"
#include "Brick.h"
#include "Player.h"
#include "MovableObject.h"
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
    void ResetBall();
    float _startVelocityMagnitude;
    void CheckCollision(Figure *Figure);
protected:
    void FixedUpdate() override;
    void ConstraintRestrictions() override;
public:
    Ball(
            JavaCppAdapter *adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
    Color color, bool registerTouch, Vector2 fieldSize, Vector2 velocity, float startVelocityMagnitude, float deltaTime);
    ~Ball();
    void StartMovement();
    GenericEvent<> OnLoss;


};


#endif //ARKANOID_BALL_H
