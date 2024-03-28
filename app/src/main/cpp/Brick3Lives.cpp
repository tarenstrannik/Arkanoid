//
// Created by taren on 27.03.2024.
//

#include "ScreenObjects/Brick3Lives.h"
Brick3Lives::Brick3Lives(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, int id,
             Vector2 position, Vector2 size):Brick(adapter, gameManager, parameters, id,
position, size){
    _curPrice=_startPriceBrick3Lives;
    _curLives=_startLivesBrick3Lives;
    SetColor(_startColorBrick3Lives);
    _curVelocityMultiplicator=_startVelocityMultiplicatorBrick3Lives;

    _startPrice=_startPriceBrick3Lives;
    _startLives=_startLivesBrick3Lives;
    _startColor=_startColorBrick3Lives;
    _startVelocityMultiplicator=_startVelocityMultiplicatorBrick3Lives;
};
void Brick3Lives::FixedUpdate() {
    Brick::FixedUpdate();
}

void Brick3Lives::ResetBrick() {
    Brick::ResetBrick();
}

void Brick3Lives::Collide() {
    Brick::Collide();
    switch(_curLives)
    {
        case 2:
            _curPrice=_priceWithTwoLives;
            _curVelocityMultiplicator=_twoLivesVelocityMultiplicator;
            SetColor(_colorWithTwoLives);
            break;
        case 1:
            _curPrice=_priceWithOneLive;
            _curVelocityMultiplicator=_oneLiveVelocityMultiplicator;
            SetColor(_colorWithOneLive);
            break;
    }
}
