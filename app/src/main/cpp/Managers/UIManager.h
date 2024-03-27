//
// Created by taren on 25.03.2024.
//

#ifndef ARKANOID_UIMANAGER_H
#define ARKANOID_UIMANAGER_H

#include "../BaseClasses/Manager.h"

class GameManager;

class UIManager: public Manager {
protected:
    void SetScore(int score);
    void SetLives(int lives);
public:
    UIManager(JavaCppAdapter* adapter, GameManager* gameManager,Parameters* parameters);
    void ResetUI();
};


#endif //ARKANOID_UIMANAGER_H
