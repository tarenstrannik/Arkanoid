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

Brick::Brick(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id, Vector2 position, Vector2 size
             ) : Figure(adapter, id, parameters->_brickShape, position, size, parameters->_brickColor, false)
             {
    _topBorder=position.y-_size.y/2;
    _bottomBorder=position.y+_size.y/2;
    _leftBorder=position.x-_size.x/2;
    _rightBorder=position.x+_size.x/2;

    _price=parameters->_brickPrice;
    _curLives=parameters->_brickLives;
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
    OnCollision.Invoke(_price);
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
