//
// Created by taren on 23.03.2024.
//

#include "Brick.h"
#include "GameManager.h"

Brick::~Brick()
{
    OnDestroy.Invoke(this);
    Figure::~Figure();
}

Brick::Brick(JavaCppAdapter* adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
             Color color, bool registerTouch) : Figure(adapter, id, shape, position, size, color, registerTouch) {
    _topBorder=position.y-_size.y/2;
    _bottomBorder=position.y+_size.y/2;
    _leftBorder=position.x-_size.x/2;
    _rightBorder=position.x+_size.x/2;
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
