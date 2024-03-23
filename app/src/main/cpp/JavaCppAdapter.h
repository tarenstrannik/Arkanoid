//
// Created by taren on 23.03.2024.
//

#ifndef ARKANOID_JAVACPPADAPTER_H
#define ARKANOID_JAVACPPADAPTER_H

#include <jni.h>
#include "GenericEvent.h"

class JavaCppAdapter {
    private:
    JNIEnv* _env;
    jobject _activityObj;
public:
    void UpdateScore(int newScore);

    JavaCppAdapter(JNIEnv* env, jobject activityObj);
    ~JavaCppAdapter();

    GenericEvent<> FixedUpdateEvent;
};


#endif //ARKANOID_JAVACPPADAPTER_H
