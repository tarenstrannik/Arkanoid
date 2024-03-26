//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H


#include "../BaseClasses/Figure.h"


class GameManager;

class Brick: public Figure {
protected:
    float _topBorder;
    float _bottomBorder;
    float _leftBorder;
    float _rightBorder;
    int _price;
    int _curLives;
    void FixedUpdate() override;
public:
    GenericEvent<Figure*> OnDestroy;
    Brick(JavaCppAdapter* adapter, GameManager* gameManager, int id, Shapes shape, Vector2 position, Vector2 size,
          Color color, bool registerTouch, int price, int lives);
    ~Brick();
    float GetTopBorder() override;
    float GetBottomBorder() override;
    float GetLeftBorder() override;
    float GetRightBorder() override;
    virtual void Collide();
    GenericEvent<int> OnCollision;
};


#endif //ARKANOID_BRICK_H
