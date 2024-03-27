//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_JAVACPPADAPTER_H
#define ARKANOID_JAVACPPADAPTER_H

#include <jni.h>
#include "../BaseClasses/GenericEvent.h"
#include "../Structures/Vector2.h"
#include "../Structures/Color.h"

class JavaCppAdapter {
    private:
    JNIEnv* _env;
    jobject _activityObj;
public:
    void UpdateScore(int newScore);
    void UpdateLives(int newLives);
    void CreateFigure(
            int id,
            int shapeType,
            int positionX,
            int positionY,
            int sizeX,
            int sizeY,
            int colorR,
            int colorG,
            int colorB,
            bool registerTouch
    );
    void DestroyFigure(int id);
    void PlaySound();
    JavaCppAdapter(JNIEnv* env, jobject activityObj);
    ~JavaCppAdapter();

    GenericEvent<> OnFixedUpdate;
    GenericEvent<> OnRestartGame;
    GenericEvent<Vector2> OnTouch;
    void GameOver(int score);
    void SetPosition(int id,Vector2 position);
    void SetColor(int id,Color color);
};


#endif //ARKANOID_JAVACPPADAPTER_H
