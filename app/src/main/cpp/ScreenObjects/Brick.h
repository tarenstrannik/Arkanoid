//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H


#include "../BaseClasses/Figure.h"
#include "../Parameters.h"


class GameManager;

class Brick: public Figure {
protected:
    float _topBorder;
    float _bottomBorder;
    float _leftBorder;
    float _rightBorder;

    int _startPrice=1;
    int _startLives=1;
    Color _startColor=Color(100,0,100);
    float _startVelocityMultiplicator=1.05f;

    int _curPrice;
    int _curLives;
    float _curVelocityMultiplicator;
    void FixedUpdate() override;

public:
    GenericEvent<Brick*> OnDeactivation;
    Brick(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
          Vector2 position, Vector2 size);
    ~Brick();
    float GetTopBorder() override;
    float GetBottomBorder() override;
    float GetLeftBorder() override;
    float GetRightBorder() override;
    virtual void Collide();
    GenericEvent<int> OnCollision;
    float GetVelocityMultiplicator();
    virtual void ResetBrick();
};


#endif //ARKANOID_BRICK_H
