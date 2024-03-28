//
// Created by taren on 27.03.2024.
//

#include "Brick2Lives.h"
Brick2Lives::Brick2Lives(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
                         Vector2 position, Vector2 size):Brick(adapter, gameManager, parameters, id,
                                                               position, size){
    _curPrice=_startPriceBrick2Lives;
    _curLives=_startLivesBrick2Lives;
    SetColor(_startColorBrick2Lives);
    _curVelocityMultiplicator=_startVelocityMultiplicatorBrick2Lives;

    _startPrice=_startPriceBrick2Lives;
    _startLives=_startLivesBrick2Lives;
    _startColor=_startColorBrick2Lives;
    _startVelocityMultiplicator=_startVelocityMultiplicatorBrick2Lives;
};
void Brick2Lives::FixedUpdate() {
    Brick::FixedUpdate();
}


void Brick2Lives::Collide() {
    Brick::Collide();
    _curPrice=_priceWithOneLive;
    SetColor(_colorWithOneLive);
    _curVelocityMultiplicator=_oneLiveVelocityMultiplicator;
}

void Brick2Lives::ResetBrick() {
    Brick::ResetBrick();
}
