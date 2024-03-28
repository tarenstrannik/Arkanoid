//
// Created by taren on 27.03.2024.
//

#ifndef ARKANOID_BRICK2LIVES_H
#define ARKANOID_BRICK2LIVES_H


#include "Brick.h"

class Brick2Lives: public Brick {
protected:
    int _startPriceBrick2Lives=2;
    int _startLivesBrick2Lives=2;
    Color _startColorBrick2Lives=Color(255,255,0);
    float _startVelocityMultiplicatorBrick2Lives=1.1f;

    int _priceWithOneLive=1;
    Color _colorWithOneLive=Color(100,0,100);
    float _oneLiveVelocityMultiplicator=1.05f;
    void FixedUpdate() override;
public:
    void ResetBrick() override;
    void Collide() override;
    Brick2Lives(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
            Vector2 position, Vector2 size);
};


#endif //ARKANOID_BRICK2LIVES_H
