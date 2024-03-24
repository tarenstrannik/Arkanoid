//
// Created by taren on 24.03.2024.
//

#ifndef ARKANOID_PLAYER_H
#define ARKANOID_PLAYER_H

#include "Figure.h"


class Player: public Figure {
private:
    Vector2 _fieldSize;
protected:
    void FixedUpdate() override;
    void SetPosition(Vector2 position) override;
public:
    Player(
           JavaCppAdapter *adapter, int id, Shapes shape, Vector2 position, Vector2 size,
           Color color, bool registerTouch, Vector2 fieldSize);
    ~Player();
};


#endif //ARKANOID_PLAYER_H
