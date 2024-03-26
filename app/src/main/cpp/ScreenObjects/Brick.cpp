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

Brick::Brick(JavaCppAdapter* adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
             Color color, bool registerTouch, int price, int lives) : Figure(adapter, id, shape, position, size, color, registerTouch) {
    _topBorder=position.y-_size.y/2;
    _bottomBorder=position.y+_size.y/2;
    _leftBorder=position.x-_size.x/2;
    _rightBorder=position.x+_size.x/2;

    _price=price;
    _curLives=lives;
    OnCollision = GenericEvent<int>();
    OnDestroy = GenericEvent<Figure*>();
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

}
void Brick::FixedUpdate()
{
    Figure::FixedUpdate();
    if(_curLives<=0)
    {
        delete this;
    }
}
