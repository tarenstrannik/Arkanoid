//
// Created by taren on 25.03.2024.
//

#ifndef ARKANOID_UIMANAGER_H
#define ARKANOID_UIMANAGER_H

#include "GameManager.h"
class GameManager;

class UIManager {
private:
    JavaCppAdapter* _javaCppAdapter;
    GameManager* _gameManager;
    int _startLives;
    int _startScore;
    void SetScore(int score);
    void SetLives(int lives);
    void ResetUI();
public:
    UIManager(JavaCppAdapter* adapter, GameManager* gameManager, int lives, int score);
};


#endif //ARKANOID_UIMANAGER_H
