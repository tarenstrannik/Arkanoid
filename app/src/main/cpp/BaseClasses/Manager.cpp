//
// Created by taren on 27.03.2024.
//

#include "Manager.h"

Manager::Manager(JavaCppAdapter* adapter, GameManager* gameManager, Parameters* parameters) {
    _javaCppAdapter=adapter;
    _gameManager=gameManager;
    _parameters=parameters;

}
