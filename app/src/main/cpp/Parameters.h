//
// Created by taren on 27.03.2024.
//

#ifndef ARKANOID_PARAMETERS_H
#define ARKANOID_PARAMETERS_H


#include "Structures/Color.h"
#include "Enums/Shapes.h"

struct Parameters {
    float _playerWidthFraction = 0.2f;//from screen
    float _playerWidthToHeight = 4.0f;
    float _playerStartPositionX = 0.5f;//from screen width
    float _playerStartPositionY = 0.9f;//from screen height
    Color _playerColor = Color(100, 100, 0);
    Shapes _playerShape=Shapes::RECTANGLE;
    int _playerLives = 3;
    int _playerScore = 0;

    //ball params
    float _ballWidthFraction = 0.05f;//from screen
    float _ballStartPositionX = 0.5f;//from screen width
    float _ballStartPositionY = 0.8f;//from screen height
    Shapes _ballShape=Shapes::CIRCLE;
    Color _ballColor = Color(0, 100, 255);
    float _ballStartVelocityMagnitude = 300.0f;
    float _ballMaxStartAngleToVertical=45.0f;
    //bricks factory params
    int _rows = 5;
    int _columns = 5;

    //bricks params
    float _brickDecreasingCoef=0.9f;//to let space between bricks
    float _brickWidthToHeight=2;
    Shapes _brickShape=Shapes::RECTANGLE;
    //rest brick params in brick.h files aka prefabs
};


#endif //ARKANOID_PARAMETERS_H
