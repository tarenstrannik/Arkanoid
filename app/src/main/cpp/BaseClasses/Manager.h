//
// Created by taren on 27.03.2024.
//

#ifndef ARKANOID_MANAGER_H
#define ARKANOID_MANAGER_H


#include "../Managers/JavaCppAdapter.h"
#include "../Structures/Parameters.h"
#include "../Managers/GameManager.h"

class Manager {
protected:
    JavaCppAdapter* _javaCppAdapter;
    GameManager* _gameManager;
    Parameters* _parameters;
public:
    Manager(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters);
};


#endif //ARKANOID_MANAGER_H
