//
// Created by taren on 25.03.2024.
//

#include "Ball.h"
Ball::Ball(JavaCppAdapter *adapter, int id, Shapes shape, Vector2 position, Vector2 size,
               Color color, bool registerTouch, Vector2 fieldSize, Vector2 velocity, float deltaTime) :
        Figure(adapter, id, shape, position, size, color, registerTouch), MovableObject(fieldSize,velocity,deltaTime)

{
    _fieldSize=fieldSize;
    _startMovement= Figure::_javaCppAdapter->TouchEvent.Subscribe([this](Vector2 position) {
        StartMovement();
    });
}

Ball::~Ball(){
    Figure::_javaCppAdapter->TouchEvent.Unsubscribe(_startMovement);
}
void Ball::FixedUpdate()
{
    Figure::FixedUpdate();
    Move();
    Ball::ConstraintRestrictions();
}


void Ball::ConstraintRestrictions() {
    Figure::ConstraintRestrictions();
    if(IsCollisionWithWalls())
    {
        auto velocity=GetVelocity();
        SetVelocity(Vector2(-velocity.x,velocity.y));
    }
    else if(IsCollisionWithCeiling())
    {
        auto velocity=GetVelocity();
        SetVelocity(Vector2(velocity.x,-velocity.y));
    }
    else if(IsCollisionWithFloor())
    {
        ResetBall();
        LossEvent.Invoke();
    }
}

void Ball::StartMovement() {
    Figure::_javaCppAdapter->TouchEvent.Unsubscribe(_startMovement);
    SetVelocity(Vector2(0,-300));
}

void Ball::Move() {
    Vector2 newPosition = _position + _velocity * _deltaTime;
    SetPosition(newPosition);
}

bool Ball::IsCollisionWithWalls() {
    return _position.x<=_size.x/2 || _position.x>=_fieldSize.x-_size.x/2;
}

bool Ball::IsCollisionWithCeiling() {
    return _position.y<=_size.y/2;
}

bool Ball::IsCollisionWithFloor() {
    return _position.y>=_fieldSize.y-_size.y/2;
}

void Ball::ResetBall()
{
    SetVelocity(Vector2(0,0));
    SetPosition(_startPosition);
    _startMovement= Figure::_javaCppAdapter->TouchEvent.Subscribe([this](Vector2 position) {
        StartMovement();
    });
}
