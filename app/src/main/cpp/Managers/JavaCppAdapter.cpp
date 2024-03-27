//
// Created by taren on 23.03.2024.
//

#include "JavaCppAdapter.h"
#include "GameManager.h"

JavaCppAdapter::JavaCppAdapter(JNIEnv* env, jobject activityObj) : _env(env), _activityObj(activityObj)
{
    OnFixedUpdate = GenericEvent<>();
    OnRestartGame = GenericEvent<>();
    OnTouch = GenericEvent<Vector2>();
}

JNIEnv* g_env;
jobject g_mainActivityObj;
JavaCppAdapter* g_javaCppAdapter = nullptr;

extern "C" JNIEXPORT void JNICALL
    Java_com_example_Arkanoid_MainActivity_AdapterInitiateJavaCppAdapter(
        JNIEnv *env,
        jobject instance/* this */
) {
    g_env=env;
    g_mainActivityObj = g_env->NewGlobalRef(instance);
    g_javaCppAdapter = new JavaCppAdapter(g_env, g_mainActivityObj);
}
extern "C" JNIEXPORT void JNICALL
Java_com_example_Arkanoid_MainActivity_AdapterInitiateCPPGameManager(
        JNIEnv *env,
        jobject instance/* this */,
        int width,
        int height,
        float deltaTime
) {
    GameManager* gameManager = new GameManager(g_javaCppAdapter, Vector2((float)width, (float)height), deltaTime);
}
extern "C" JNIEXPORT void JNICALL
    Java_com_example_Arkanoid_MainActivity_AdapterFixedUpdate(
        JNIEnv *env,
        jobject /* this */
) {
    if (g_javaCppAdapter != nullptr)
    {
        g_javaCppAdapter->OnFixedUpdate.Invoke();
    }
}

void JavaCppAdapter::UpdateScore(int newScore) {

    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeUpdateScore", "(I)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID, newScore);
}
void JavaCppAdapter::UpdateLives(int newLives) {

    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeUpdateLives", "(I)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID, newLives);
}
void JavaCppAdapter::PlaySound() {
    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativePlaySound", "()V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID);
}
extern "C" JNIEXPORT void JNICALL
Java_com_example_Arkanoid_MainActivity_AdapterProcessTouch(JNIEnv *env, jobject , int x,
                                                          int y) {
    if (g_javaCppAdapter != nullptr)
    {
        g_javaCppAdapter->OnTouch.Invoke(Vector2(x, y));
    }
}
extern "C" JNIEXPORT void JNICALL
Java_com_example_Arkanoid_MainActivity_AdapterRestartGame(JNIEnv *env, jobject) {
    if (g_javaCppAdapter != nullptr)
    {
        g_javaCppAdapter->OnRestartGame.Invoke();
    }
}
void JavaCppAdapter::CreateFigure(
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
) {

    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeCreateFigure", "(IIIIIIIIIZ)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID,
                          id,
                          shapeType,
                          positionX,
                          positionY,
                          sizeX,
                          sizeY,
                          colorR,
                          colorG,
                          colorB,
                          registerTouch
    );
}
void JavaCppAdapter::SetPosition(int id, Vector2 position) {
    // Вызов метода NativeUpdateScore в экземпляре MainActivity
    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeSetPosition", "(III)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID, id, (int)position.x,(int)position.y);
}

void JavaCppAdapter::DestroyFigure(int id) {

    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeDestroyFigure", "(I)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID, id);
}

void JavaCppAdapter::GameOver(int score) {
    jclass clazz = g_env->GetObjectClass(g_mainActivityObj);
    jmethodID methodID = g_env->GetMethodID(clazz, "NativeGameOver", "(I)V");
    g_env->CallVoidMethod(g_mainActivityObj, methodID, score);
}


