//
// Created by taren on 25.03.2024.
//

#include "Random.h"
#include <iostream>
#include <random>

float Random::Range(float start, float end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(start, end);
    return dis(gen);;
}
