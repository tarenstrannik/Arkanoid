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

    _gameManager->OnFigureCollisionCheck.Subscribe([this](Figure* figure){
        CheckCollision(figure);
    });
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

void Ball::CheckCollision(Figure* figure)
{
    float ballLeft=GetPosition().x-_size.x/2;
    float ballRight=GetPosition().x+_size.x/2;
    float ballTop=GetPosition().y-_size.y/2;
    float ballBottom=GetPosition().y+_size.y/2;

    float figureLeft=figure->GetLeftBorder();
    float figureRight=figure->GetRightBorder();;
    float figureTop=figure->GetTopBorder();;
    float figureBottom=figure->GetBottomBorder();;

//coordinates from top edge of screen)
    if(ballRight<figureLeft || ballLeft>figureRight || ballTop >figureBottom || ballBottom<figureTop)
    {
        return;
    }
    _javaCppAdapter->PlaySound();
    auto curVelocity= GetVelocity();
    Vector2 newVelocity=Vector2::zero();

    if (Brick* brick = dynamic_cast<Brick*>(figure))
    {
        curVelocity *=_parameters->_ballVelocityIncrement;
        brick->Collide();
    }

    if(ballLeft>=figureLeft&& ballRight<=figureRight
        ||(ballRight-figureLeft>ballBottom-figureTop)
        || (figureRight-ballLeft>ballBottom-figureTop)
        ||(ballRight-figureLeft>figureBottom-ballTop)
        || (figureRight-ballLeft>figureBottom-ballTop)
    )
    {
        newVelocity=Vector2(curVelocity.x,-curVelocity.y);
    }
    else if(ballBottom<=figureBottom && ballTop>=figureTop
            ||(ballRight-figureLeft<ballBottom-figureTop)
            || (figureRight-ballLeft<ballBottom-figureTop)
            ||(ballRight-figureLeft<figureBottom-ballTop)
            || (figureRight-ballLeft<figureBottom-ballTop)
    )
    {
        newVelocity=Vector2(-curVelocity.x,curVelocity.y);
    }
    else
    {
        newVelocity=-curVelocity;
    }
    if (MovableObject* movable = dynamic_cast<MovableObject*>(figure))
    {
        auto playerVelocity=movable->GetVelocity();
        newVelocity += movable->GetVelocity();
    }
    SetVelocity(newVelocity);
}
