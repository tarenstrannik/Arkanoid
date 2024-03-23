#include <jni.h>
#include <string>
#include "GameSceneObject.h"
#include "GameManager.h"

GameManager _gameManager;

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
Java_com_example_Arkanoid_MainActivity_CreateGameManager(
        JNIEnv *env,
        jobject /* this */
        ) {

        _gameManager = GameManager();

}

extern "C" JNIEXPORT void

JNICALL
Java_com_example_Arkanoid_MainActivity_FixedUpdate(
        JNIEnv *env,
        jobject /* this */
) {
    _gameManager.FixedUpdate();
}

extern "C" JNIEXPORT void

JNICALL
        Java_com_example_Arkanoid_MainActivity_NativeUpdateScore(
                JNIEnv *env,
                jobject mainActivityInstance/* this */,
                int score
        ) {

    const jclass  mainActivityCls = env->GetObjectClass(mainActivityInstance);
    const jmethodID methodID =
            env->GetMethodID(mainActivityInstance, "NativeUpdateScore", "(I)V");
    if(methodID == nullptr)
}