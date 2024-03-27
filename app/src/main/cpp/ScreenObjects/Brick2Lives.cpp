//
// Created by taren on 27.03.2024.
//

#include "Brick2Lives.h"
Brick2Lives::Brick2Lives(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
                         Vector2 position, Vector2 size):Brick(adapter, gameManager, parameters, id,
                                                               position, size){
    _curPrice=_startPrice;
    _curLives=_startLives;
    SetColor(_startColor);
    _curVelocityMultiplicator=_startVelocityMultiplicator;
};
void Brick2Lives::FixedUpdate() {
    Brick::FixedUpdate();
}

void Brick2Lives::ResetBrick() {
    Brick::ResetBrick();
}

void Brick2Lives::Collide() {
    Brick::Collide();
    _curPrice=_priceWithOneLive;
    SetColor(_colorWithOneLive);
    _curVelocityMultiplicator=_oneLiveVelocityMultiplicator;
}
