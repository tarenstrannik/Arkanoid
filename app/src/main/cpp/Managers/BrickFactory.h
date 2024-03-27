//
// Created by taren on 26.03.2024.
//

#ifndef ARKANOID_BRICKFACTORY_H
#define ARKANOID_BRICKFACTORY_H


#include "../ScreenObjects/Brick.h"
#include<list>
#include "../BaseClasses/Manager.h"
#include "../ScreenObjects/Brick2Lives.h"
#include "../ScreenObjects/Brick3Lives.h"

class BrickFactory: public Manager {
protected:
    Vector2* _fieldSize;
    std::list<Brick*> _bricks;
    void Generate();
    void Clear();
    void RemoveBrickFromBricks(Brick *brick);
    template<typename T>
    void CreateBrickOfType(Vector2 position, Vector2 size);
public:
    BrickFactory(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters, Vector2* fieldSize);
    GenericEvent<Brick*> OnBrickCreation;



};


#endif //ARKANOID_BRICKFACTORY_H
