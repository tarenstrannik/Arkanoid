//
// Created by taren on 24.03.2024.
//

#include "Player.h"
#include "../Managers/GameManager.h"

Player::Player(JavaCppAdapter *adapter, GameManager* gameManager, Parameters* parameters, int id,
                Vector2 position, Vector2 size, Vector2* fieldSize, float deltaTime) :
               Figure(adapter, id, parameters->_playerShape, position, size, parameters->_playerColor, true),
               MovableObject(fieldSize,Vector2::zero(),deltaTime)

{
    _gameManager=gameManager;
    _prevPosition=position;
    _topBorder=position.y-_size.y/2;
    _bottomBorder=position.y+_size.y/2;
    _setPosition=Figure::_javaCppAdapter->OnTouch.Subscribe([this](Vector2 position) {
        SetPosition(position);
    });
    _gameManager->OnRoundLoss.Subscribe([this](int value){
       ResetPosition(value);
    });
    _gameManager->OnNewRound.Subscribe([this](){
        ResetPosition(0);
    });

}

Player::~Player(){
        Figure::_javaCppAdapter->OnTouch.Unsubscribe(_setPosition);
}
void Player::FixedUpdate()
{
    Figure::FixedUpdate();
    Player::ConstraintRestrictions();
    Player::UpdateVelocity();
}

void Player::SetPosition(Vector2 position)
{
    _position= Vector2(position.x,_position.y);
    Figure::SetPosition(_position);
}

void Player::ConstraintRestrictions() {
    Figure::ConstraintRestrictions();
    if(_position.x<=_size.x/2)
    {
        SetPosition(Vector2(_size.x/2,_position.y));
    }
    else if(_position.x>=_fieldSize->x-_size.x/2)
    {
        SetPosition(Vector2(_fieldSize->x-_size.x/2,_position.y));
    }
}

void Player::UpdateVelocity() {
    Vector2 newVelocity = (_position - _prevPosition) / _deltaTime;
    Player::SetVelocity(newVelocity);
    _prevPosition=_position;
}

void Player::ResetPosition(int value)
{
    Player::SetPosition(_startPosition);
}

float Player::GetTopBorder() {
    return _topBorder;
}

float Player::GetBottomBorder() {
    return _bottomBorder;
}
