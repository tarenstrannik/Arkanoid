//
// Created by taren on 23.03.2024.
//

#include "JavaCppAdapter.h"
#include "GameManager.h"

JavaCppAdapter::JavaCppAdapter(JNIEnv* env, jobject activityObj) : _env(env), _activityObj(activityObj)
{
    FixedUpdateEvent = GenericEvent<>();
    GameManager* gameManager = new GameManager(this);
}

JNIEnv* g_env;
jobject g_mainActivityObj;
JavaCppAdapter* g_javaCppAdapter = nullptr;

extern "C" JNIEXPORT void JNICALL
    Java_com_example_Arkanoid_MainActivity_InitiateJavaCppAdapter(
        JNIEnv *env,
        jobject instance/* this */
) {
    g_env=env;
    g_mainActivityObj = g_env->NewGlobalRef(instance);
    g_javaCppAdapter = new JavaCppAdapter(g_env, g_mainActivityObj);
}

extern "C" JNIEXPORT void JNICALL
    Java_com_example_Arkanoid_MainActivity_FixedUpdate(
        JNIEnv *env,
        jobject /* this */
) {
    if (g_javaCppAdapter != nullptr)
    {
        g_javaCppAdapter->FixedUpdateEvent.Invoke();
    }
}

void JavaCppAdapter::UpdateScore(int newScore) {
    // Вызов метода NativeUpdateScore в экземпляре MainActivity
    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeUpdateScore", "(I)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID, newScore);
}
