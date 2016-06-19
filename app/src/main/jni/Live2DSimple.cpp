
#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>

#include "Live2DSimple.h"

#include "Live2D.h"
#include "Live2DModelOpenGL.h"
#include "util/UtSystem.h"

#include "live2dframework/Live2DFramework.h"
#include "PlatformManager.h"
#include "L2DModel.h"

using namespace live2d;
using namespace live2d::framework;

static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}

L2DModel*model;
string assetsPath;

static bool isLive2DInstantiated = false;

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnCreate(JNIEnv *env, jobject thiz, jstring jAssetsPath) {
    currentJNIEnv = env;

    const char* nativeString = env->GetStringUTFChars(jAssetsPath, 0);
    string _assetsPath(nativeString);
    assetsPath = _assetsPath;
    env->ReleaseStringUTFChars(jAssetsPath, nativeString);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceCreated(JNIEnv* env, jobject thiz) {
	LOGI("nativeOnSurfaceCreated");

    currentJNIEnv = env;


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
    model = new L2DModel();

    const char* fileChar = "haru.model.json";
    string filename(fileChar);

    model->load(assetsPath, filename);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height) {
    currentJNIEnv = env;
	glViewport(0, 0, width, height);
    model->setMatrix(width, height);
}


JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnDrawFrame(JNIEnv* env, jobject thiz) {
    currentJNIEnv = env;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    model->draw();
}
