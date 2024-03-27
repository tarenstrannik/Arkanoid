//
// Created by taren on 23.03.2024.
//

#include "Brick.h"
#include "../Managers/GameManager.h"

Brick::~Brick()
{
    OnDestroy.Invoke(this);
    Figure::~Figure();
}

Brick::Brick(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
             Vector2 position, Vector2 size
             ) : Figure(adapter, id, parameters->_brickShape, position, size,
                        Color(0,0,0), false)
             {
    _topBorder=position.y-_size.y/2;
    _bottomBorder=position.y+_size.y/2;
    _leftBorder=position.x-_size.x/2;
    _rightBorder=position.x+_size.x/2;

    _curPrice=_startPrice;
    _curLives=_startLives;
    SetColor(_startColor);
    _curVelocityMultiplicator=_startVelocityMultiplicator;

    OnCollision = GenericEvent<int>();
    OnDestroy = GenericEvent<Brick*>();
}

float Brick::GetTopBorder() {
    return _topBorder;
}

float Brick::GetBottomBorder() {
    return _bottomBorder;
}

float Brick::GetLeftBorder() {
    return _leftBorder;
}

float Brick::GetRightBorder() {
    return _rightBorder;
}

void Brick::Collide()
{
    _curLives--;
    OnCollision.Invoke(_curPrice);
    if(_curLives<=0)
    {
        Destroy();
    }
}
void Brick::FixedUpdate()
{
    Figure::FixedUpdate();
}

void Brick::Destroy() {
    delete this;
}

float Brick::GetVelocityMultiplicator() {
    return _curVelocityMultiplicator;
}

void Brick::ResetBrick() {
    _curPrice=_startPrice;
    _curLives=_startLives;
    _color=_startColor;
}
