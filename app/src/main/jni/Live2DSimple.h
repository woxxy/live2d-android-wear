#include <jni.h>

#define LOG_TAG "jni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////

extern "C" {
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeSetPngManager(JNIEnv* env, jobject thiz, jobject pngmgr);

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadTexture(JNIEnv* env, jobject thiz, jint no, jstring path, jobject pngmgr);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadLive2DModel(JNIEnv* env, jobject thiz, jstring path);

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceCreated(JNIEnv* env, jobject thiz);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceDestroyed(JNIEnv* env, jobject thiz);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnDrawFrame(JNIEnv* env, jobject thiz);

}
