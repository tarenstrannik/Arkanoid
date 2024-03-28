//
// Created by taren on 25.03.2024.
//

#include "Ball.h"
#include "../StaticClasses/Random.h"
#include "../Managers/GameManager.h"

Ball::Ball(JavaCppAdapter *adapter, GameManager* gameManager,  Parameters* parameters,int id, Vector2 position, Vector2 size,
           Vector2* fieldSize, float deltaTime) :
        Figure(adapter, id, parameters->_ballShape, position, size, parameters->_ballColor, false),
        MovableObject(fieldSize,Vector2::zero(),deltaTime)

{
    _gameManager=gameManager;
    _parameters=parameters;
    _fieldSize=fieldSize;
    OnLoss=GenericEvent<>();

    _gameManager->OnNewRound.Subscribe([this](){
        ResetBall(0);
    });
    _gameManager->OnRoundLoss.Subscribe([this](int value){
        ResetBall(value);
    });
    _gameManager->OnGameOver.Subscribe([this](){
        Figure::_javaCppAdapter->OnTouch.Unsubscribe(_startMovement);
    });
}

Ball::~Ball(){
    Figure::_javaCppAdapter->OnTouch.Unsubscribe(_startMovement);
}
void Ball::FixedUpdate()
{
    Figure::FixedUpdate();
    Move();
    Ball::ConstraintPosition();
}


void Ball::ConstraintPosition() {
    Figure::ConstraintPosition();
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
    else if(IsCollisionWithFloor()||IsOutOfBound())
    {
        OnLoss.Invoke();
    }
}

void Ball::StartMovement() {
    Figure::_javaCppAdapter->OnTouch.Unsubscribe(_startMovement);
    float startXVelocityRange=_parameters->_ballStartVelocityMagnitude
            * sin(M_PI* _parameters->_ballMaxStartAngleToVertical/180);

    auto velocityX= Random::Range(-startXVelocityRange,startXVelocityRange);
    auto velocityY=sqrtf(pow(_parameters->_ballStartVelocityMagnitude,2) - pow(velocityX,2));
    SetVelocity(Vector2(velocityX,-velocityY));
}

void Ball::Move() {
    Vector2 newPosition = _position + _velocity * _deltaTime;
    SetPosition(newPosition);
}

bool Ball::IsCollisionWithWalls() {
    return _position.x<=_size.x/2 || _position.x>=_fieldSize->x-_size.x/2;
}


bool Ball::IsCollisionWithCeiling() {
    return _position.y<=_size.y/2;
}
bool Ball::IsOutOfBound() {
    return _position.x<0 || _position.x>_fieldSize->x||_position.y<0;
}
bool Ball::IsCollisionWithFloor() {
    return _position.y>=_fieldSize->y-_size.y/2;
}

void Ball::ResetBall(int value)
{
    SetVelocity(Vector2(0,0));
    SetPosition(_startPosition);
    _startMovement= Figure::_javaCppAdapter->OnTouch.Subscribe([this](Vector2 position) {
        StartMovement();
    });
}

bool Ball::CheckCollision(Figure* figure)
{
    float ballLeft=GetPosition().x-_size.x/2;
    float ballRight=GetPosition().x+_size.x/2;
    float ballTop=GetPosition().y-_size.y/2;
    float ballBottom=GetPosition().y+_size.y/2;

    Vector2 ballPosition=GetPosition();
    Vector2 figurePosition=figure->GetPosition();

    float figureLeft=figure->GetLeftBorder();
    float figureRight=figure->GetRightBorder();;
    float figureTop=figure->GetTopBorder();;
    float figureBottom=figure->GetBottomBorder();;

//coordinates from top edge of screen)
    if(ballRight<figureLeft || ballLeft>figureRight || ballTop >figureBottom || ballBottom<figureTop)
    {
        return false;
    }
    _javaCppAdapter->PlaySound();
    auto curVelocity= GetVelocity();
    Vector2 newVelocity=Vector2::zero();

    if (Brick* brick = dynamic_cast<Brick*>(figure))
    {
        curVelocity *=brick->GetVelocityMultiplicator();
        brick->Collide();
    }

    if(curVelocity.y<0)
    {
        if(curVelocity.x>=0)
        {
            if(ballPosition.x>figurePosition.x)
            {
                newVelocity = Vector2(curVelocity.x, -curVelocity.y);
            }
            else if(ballPosition.y<figurePosition.y)
            {
                newVelocity = Vector2(-curVelocity.x, curVelocity.y);
            }
            else {
                if ((ballLeft >= figureLeft && ballRight <= figureRight)
                    || (ballRight - figureLeft > figureBottom - ballTop)) {
                    newVelocity = Vector2(curVelocity.x, -curVelocity.y);
                } else if (ballBottom <= figureBottom && ballTop >= figureTop
                           || (ballRight - figureLeft < figureBottom - ballTop)) {
                    newVelocity = Vector2(-curVelocity.x, curVelocity.y);
                } else {
                    newVelocity = -curVelocity;
                }
            }
        }
        else
        {
            if(ballPosition.x<figurePosition.x)
            {
                newVelocity = Vector2(curVelocity.x, -curVelocity.y);
            }
            else if(ballPosition.y<figurePosition.y)
            {
                newVelocity = Vector2(-curVelocity.x, curVelocity.y);
            }
            else {
                if ((ballLeft >= figureLeft && ballRight <= figureRight)
                    || (figureRight-ballLeft > figureBottom - ballTop)) {
                    newVelocity = Vector2(curVelocity.x, -curVelocity.y);
                } else if (ballBottom <= figureBottom && ballTop >= figureTop
                           || (figureRight-ballLeft < figureBottom - ballTop)) {
                    newVelocity = Vector2(-curVelocity.x, curVelocity.y);
                } else {
                    newVelocity = -curVelocity;
                }
            }
        }
    }
    else
    {
        if(curVelocity.x>=0)
        {
            if(ballPosition.x>figurePosition.x)
            {
                newVelocity = Vector2(curVelocity.x, -curVelocity.y);
            }
            else if(ballPosition.y>figurePosition.y)
            {
                newVelocity = Vector2(-curVelocity.x, curVelocity.y);
            }
            else {
                if ((ballLeft >= figureLeft && ballRight <= figureRight)
                    || (ballRight - figureLeft > ballBottom - figureTop)) {
                    newVelocity = Vector2(curVelocity.x, -curVelocity.y);
                } else if (ballBottom <= figureBottom && ballTop >= figureTop
                           || (ballRight - figureLeft < ballBottom - figureTop)) {
                    newVelocity = Vector2(-curVelocity.x, curVelocity.y);
                } else {
                    newVelocity = -curVelocity;
                }
            }
        }
        else
        {
            if(ballPosition.x<figurePosition.x)
            {
                newVelocity = Vector2(curVelocity.x, -curVelocity.y);
            }
            else if(ballPosition.y>figurePosition.y)
            {
                newVelocity = Vector2(-curVelocity.x, curVelocity.y);
            }
            else {
                if ((ballLeft >= figureLeft && ballRight <= figureRight)
                    || (figureRight - ballLeft > ballBottom - figureTop)) {
                    newVelocity = Vector2(curVelocity.x, -curVelocity.y);
                } else if (ballBottom <= figureBottom && ballTop >= figureTop
                           || (figureRight - ballLeft < ballBottom - figureTop)) {
                    newVelocity = Vector2(-curVelocity.x, curVelocity.y);
                } else {
                    newVelocity = -curVelocity;
                }
            }
        }
    }
    if (MovableObject* movable = dynamic_cast<MovableObject*>(figure))
    {
        auto playerVelocity=movable->GetVelocity();
        newVelocity += movable->GetVelocity();
    }

    newVelocity=ConstraintVelocity(newVelocity);

    SetVelocity(newVelocity);
    return true;
}
Vector2 Ball::ConstraintVelocity(Vector2 velocity)
{
    Vector2 constrainedVelocity=velocity;
    if(abs(velocity.y) <_parameters->_ballMinYVelocity) {
        if (velocity.y >= 0)
            constrainedVelocity = Vector2(velocity.x, _parameters->_ballMinYVelocity);
        else
            constrainedVelocity = Vector2(velocity.x, -_parameters->_ballMinYVelocity);
    }
    if(constrainedVelocity.Magnitude()>_parameters->_ballMaxVelocityMagnitude)
    {
        constrainedVelocity/=constrainedVelocity.Magnitude()/_parameters->_ballMaxVelocityMagnitude;
    }
    return constrainedVelocity;
}
