#include <jni.h>
#include <string>
#include "GameSceneObject.h"

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_Arkanoid_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */,
        jstring param) {
    const char* paramStr = env->GetStringUTFChars(param, nullptr);
    std::string paramCpp(paramStr);
    // Освобождение ресурсов jstring
    env->ReleaseStringUTFChars(param, paramStr);
    std::string hello = "H from C++"+paramCpp;
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void

JNICALL
Java_com_example_Arkanoid_MainActivity_CreateGameSceneObject(
        JNIEnv *env,
        jobject /* this */,
        jfloat jupdateTimer) {
    float updateTimer=static_cast<float>(jupdateTimer);

    GameSceneObject gameSceneObject(updateTimer);
}