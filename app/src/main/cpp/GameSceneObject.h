//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_GAMESCENEOBJECT_H
#define ARKANOID_GAMESCENEOBJECT_H


class GameSceneObject {

    private:
        float _fixedUpdateTimeStep;
        void FixedUpdate();

    public:
        GameSceneObject(float timeStep);

};


#endif //ARKANOID_GAMESCENEOBJECT_H
