//
// Created by taren on 24.03.2024.
//

#include "Player.h"
Player::Player(JavaCppAdapter *adapter, int id, Shapes shape, Vector2 position, Vector2 size,
               Color color, bool registerTouch, Vector2 fieldSize) :
               Figure(adapter, id, shape, position, size, color, registerTouch)

{
    _fieldSize=fieldSize;
    Figure::_javaCppAdapter->TouchEvent.Subscribe([this](Vector2 position) {
        SetPosition(position);
    });
}

Player::~Player(){
        Figure::_javaCppAdapter->TouchEvent.Unsubscribe([this](Vector2 position) {
            SetPosition(position);
        });
}
void Player::FixedUpdate()
{
    Figure::FixedUpdate();
}

void Player::SetPosition(Vector2 position)
{
    auto playerPosition= GetPosition();
    Figure::SetPosition(Vector2(position.x,playerPosition.y));
}
