//
// Created by taren on 25.03.2024.
//

#ifndef ARKANOID_UIMANAGER_H
#define ARKANOID_UIMANAGER_H

#include "JavaCppAdapter.h"
#include "../Structures/Parameters.h"

class GameManager;

class UIManager {
private:
    JavaCppAdapter* _javaCppAdapter;
    GameManager* _gameManager;
    Parameters* _parameters;
    void SetScore(int score);
    void SetLives(int lives);

public:
    UIManager(JavaCppAdapter* adapter, GameManager* gameManager,Parameters* parameters);
    void ResetUI();
};


#endif //ARKANOID_UIMANAGER_H
