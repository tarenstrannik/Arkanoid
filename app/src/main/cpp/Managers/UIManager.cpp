//
// Created by taren on 25.03.2024.
//

#include "UIManager.h"
#include "GameManager.h"

UIManager::UIManager(JavaCppAdapter* adapter, GameManager* gameManager,Parameters* parameters)
{
    _javaCppAdapter=adapter;
    _gameManager=gameManager;
    _parameters=parameters;
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
    SetScore(_parameters->_playerScore);
    SetLives(_parameters->_playerLives);
}
