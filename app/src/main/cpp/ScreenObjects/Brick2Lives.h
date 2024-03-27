//
// Created by taren on 27.03.2024.
//

#ifndef ARKANOID_BRICK2LIVES_H
#define ARKANOID_BRICK2LIVES_H


#include "Brick.h"

class Brick2Lives: public Brick {
protected:
    int _startPrice=2;
    int _startLives=2;
    Color _startColor=Color(255,255,0);
    float _startVelocityMultiplicator=1.2f;

    int _priceWithOneLive=1;
    Color _colorWithOneLive=Color(100,0,100);
    float _oneLiveVelocityMultiplicator=1.1f;
    void FixedUpdate() override;
public:
    void ResetBrick() override;
    void Collide() override;
    Brick2Lives(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
            Vector2 position, Vector2 size);
};


#endif //ARKANOID_BRICK2LIVES_H
