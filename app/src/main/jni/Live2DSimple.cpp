
#include <jni.h>

#include <math.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/log.h>

#include "Live2D.h"
#include "Live2DModelOpenGL.h"
#include "util/UtSystem.h"

#include "live2dframework/Live2DFramework.h"
#include "Live2DSimple.h"
#include "PlatformManager.h"
#include "Global.h"

using namespace live2d;
using namespace live2d::framework;

static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}

static Live2DModelOpenGL* live2DModel;

static float matrix[] = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

static bool isLive2DInstantiated = false;

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadLive2DModel(JNIEnv* env, jobject thiz, jstring path) {
	LOGI("nativeLoadLive2DModel");

    const char* _path = env->GetStringUTFChars(path, 0);
    LOGD(_path);
    live2DModel = (Live2DModelOpenGL *) Live2DFramework::getPlatformManager()->loadLive2DModel(_path);
    live2DModel->setPremultipliedAlpha(false);

    env->ReleaseStringUTFChars(path, _path);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadTexture(JNIEnv* env, jobject thiz, jint no, jstring path, jobject pngmgr) {
	LOGI("nativeLoadTexture");

    currentJNIEnv = env;
    currentJObject = thiz;
    currentPngmgr = pngmgr;

    const char* _path = env->GetStringUTFChars(path, 0);
    Live2DFramework::getPlatformManager()->loadTexture(live2DModel, no, _path);
    env->ReleaseStringUTFChars(path, _path);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceCreated(JNIEnv* env, jobject thiz) {
	LOGI("nativeOnSurfaceCreated");

    if (isLive2DInstantiated) {
        Live2D::dispose();
    }
    Live2D::init();
    isLive2DInstantiated = true;

	printGLString("Version",    GL_VERSION);
	printGLString("Vendor",     GL_VENDOR);
	printGLString("Renderer",   GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

    Live2DFramework::setPlatformManager(new PlatformManager());
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height) {
	glViewport(0, 0, width, height);

	float w = live2DModel->getCanvasWidth();
	float h = live2DModel->getCanvasHeight();
	LOGI("Live2D Model w: %f  h: %f \n", w, h);

    matrix[0] = 1.0f / w * 3.0f;
	matrix[5] = -1.0f / w * 3.0f * ((float) width / height);

    // distance from right
	matrix[12] = -1.5f;
    // distance from bottom
	matrix[13] = 1.0f;
	live2DModel->setMatrix(matrix);
}


JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnDrawFrame(JNIEnv* env, jobject thiz) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	double t = (UtSystem::getUserTimeMSec() / 1000.0) * 2 * M_PI;
	live2DModel->setParamFloat("PARAM_ANGLE_X", (float) (30 * sin(t / 3.0)));
    live2DModel->setParamFloat("PARAM_BREATH", (float) (0.5f + 0.5f * sin(t / 3.2345)), 1);

	live2DModel->update();
	live2DModel->draw();
}
