//
// Created by taren on 26.03.2024.
//

#ifndef ARKANOID_BRICKFACTORY_H
#define ARKANOID_BRICKFACTORY_H


#include "../ScreenObjects/Brick.h"
#include<list>

class BrickFactory {
protected:
    JavaCppAdapter* _javaCppAdapter;
    GameManager* _gameManager;
    std::list<Brick*> _bricks;
    float _brickDecreasingCoef=0.9f;//to let space between bricks
    float _brickWidthToHeight=2;
    Vector2 _fieldSize;
    int _rows;
    int _columns;

    Color _color = Color(100,0,100);
    int _price=1;
    int _lives=1;
    void Generate();
    Brick* CreateBrick(Vector2 position, Vector2 size, Color color,int price,int lives);
    void Clear();

public:
    BrickFactory(JavaCppAdapter* adapter, GameManager* gameManager, Vector2 fieldSize, int rows, int columns);
    GenericEvent<Brick*> OnBrickCreation;

};


#endif //ARKANOID_BRICKFACTORY_H
