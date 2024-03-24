//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_JAVACPPADAPTER_H
#define ARKANOID_JAVACPPADAPTER_H

#include <jni.h>
#include "GenericEvent.h"
#include "Structures/Vector2.h"

class JavaCppAdapter {
    private:
    JNIEnv* _env;
    jobject _activityObj;
public:
    void UpdateScore(int newScore);
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

    JavaCppAdapter(JNIEnv* env, jobject activityObj);
    ~JavaCppAdapter();

    GenericEvent<> FixedUpdateEvent;
    GenericEvent<Vector2> TouchEvent;

    void SetPosition(int id,Vector2 position);
};


#endif //ARKANOID_JAVACPPADAPTER_H
