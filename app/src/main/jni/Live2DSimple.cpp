
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
#include "L2DModel.h"

using namespace live2d;
using namespace live2d::framework;

static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}

//static Live2DModelOpenGL* live2DModel;
L2DModel* baseModel;

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
    baseModel->loadModelData( _path);
    baseModel->getLive2DModel()->setPremultipliedAlpha(false);

    env->ReleaseStringUTFChars(path, _path);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadTexture(JNIEnv* env, jobject thiz, jint no, jstring path, jobject pngmgr) {
	LOGI("nativeLoadTexture");

    currentJNIEnv = env;
    currentJObject = thiz;
    currentPngmgr = pngmgr;

    const char* _path = env->GetStringUTFChars(path, 0);
    baseModel->loadTexture(no, _path);
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
    baseModel = new L2DModel();
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height) {
	glViewport(0, 0, width, height);
    baseModel->setMatrix(width, height);
}


JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnDrawFrame(JNIEnv* env, jobject thiz) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    baseModel->draw();

	//double t = (UtSystem::getUserTimeMSec() / 1000.0) * 2 * M_PI;
	//baseModel->getLive2DModel()->setParamFloat("PARAM_ANGLE_X", (float) (30 * sin(t / 3.0)));
    //baseModel->getLive2DModel()->setParamFloat("PARAM_BREATH", (float) (0.5f + 0.5f * sin(t / 3.2345)), 1);

    baseModel->getLive2DModel()->draw();
}
