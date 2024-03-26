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

    float _startVelocityMagnitude;
    float _velocityIncrement;
    void CheckCollision(Figure *Figure);

    float _speedIncrement;
protected:
    void FixedUpdate() override;
    void ConstraintRestrictions() override;
public:
    Ball(
            JavaCppAdapter *adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
            Color color, bool registerTouch, Vector2 fieldSize, Vector2 velocity,
            float startVelocityMagnitude, float velocityIncrement, float deltaTime);
    ~Ball();
    void StartMovement();
    GenericEvent<> OnLoss;
    void ResetBall();


};


#endif //ARKANOID_BALL_H
