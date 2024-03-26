//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H


#include "Figure.h"


class GameManager;

class Brick: public Figure {
private:
    float _topBorder;
    float _bottomBorder;
    float _leftBorder;
    float _rightBorder;
public:
    GenericEvent<Figure*> OnDestroy;
    Brick(JavaCppAdapter* adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
          Color color, bool registerTouch);
    ~Brick();
    float GetTopBorder() override;
    float GetBottomBorder() override;
    float GetLeftBorder() override;
    float GetRightBorder() override;
};


#endif //ARKANOID_BRICK_H
