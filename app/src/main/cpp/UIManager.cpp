//
// Created by taren on 25.03.2024.
//

#include "UIManager.h"

UIManager::UIManager(JavaCppAdapter* adapter,GameManager* gameManager, int lives, int score)
{
    _javaCppAdapter=adapter;
    _gameManager=gameManager;
    _startScore=score;
    _startLives=lives;
    _gameManager->OnRoundLoss.Subscribe([this](int lives) {
        SetLives(lives);
    });
    _gameManager->OnUpdateScore.Subscribe([this](int score) {
        SetScore(score);
    });
    ResetUI();
}

void UIManager::SetScore(int score)
{
    _javaCppAdapter->UpdateScore(score);
}

void UIManager::SetLives(int lives)
{
    _javaCppAdapter->UpdateLives(lives);
}

void UIManager::ResetUI()
{
    SetScore(_startScore);
    SetLives(_startLives);
}
