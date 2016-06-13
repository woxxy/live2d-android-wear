#include <stdio.h>
#include <fstream>
#include <android/log.h>
#include <util/UtFile.h>

#include "PlatformManager.h"
#include "util/UtDebug.h"
#include "Live2DModelOpenGL.h"
#include "Live2DSimple.h"
#include "Global.h"

using namespace live2d;
using namespace live2d::framework;


PlatformManager::PlatformManager(void) {}

PlatformManager::~PlatformManager(void) {}

unsigned char* PlatformManager::loadBytes(const char* path, size_t* size)
{
    unsigned char * buf = (unsigned char*) UtFile::loadFile(path, (int*) size) ;
    if(buf == NULL){
        UtDebug::error( "load file failed : file : %s @PlatformManager#loadBytes()" , path) ;
        return NULL ;
    }

    return buf;
}

void PlatformManager::releaseBytes(void* data)
{
    free(data);
}

ALive2DModel* PlatformManager::loadLive2DModel(const char* path)
{
    size_t size;
    LOGD(path);
    unsigned char* buf = loadBytes(path, &size);

    //Create Live2D Model Instance
    ALive2DModel* live2DModel = Live2DModelOpenGL::loadModel(buf, (int)size);
    this->releaseBytes(buf);
    return live2DModel;
}

L2DTextureDesc* PlatformManager::loadTexture(ALive2DModel* model, int no, const char* path)
{
    JNIEnv* env = currentJNIEnv;
    jobject pngmgr = currentPngmgr;

    jclass cls = env->GetObjectClass(pngmgr);
    jmethodID mid;

    mid = env->GetMethodID(cls, "open", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");
    jstring name = env->NewStringUTF(path);
    jobject png = env->CallObjectMethod(pngmgr, mid, name);
    env->DeleteLocalRef(name);
    env->NewGlobalRef(png);

    /* Get image dimensions */
    mid = env->GetMethodID(cls, "getWidth", "(Landroid/graphics/Bitmap;)I");
    int width = env->CallIntMethod(pngmgr, mid, png);
    mid = env->GetMethodID(cls, "getHeight", "(Landroid/graphics/Bitmap;)I");
    int height = env->CallIntMethod(pngmgr, mid, png);

    /* Get pixels */
    jintArray array = env->NewIntArray(width * height);
    env->NewGlobalRef(array);
    mid = env->GetMethodID(cls, "getPixels", "(Landroid/graphics/Bitmap;[I)V");
    env->CallVoidMethod(pngmgr, mid, png, array);

    jint *pixels = env->GetIntArrayElements(array, 0);

    for (int i = 0; i < width * height; i++) {
        int px = pixels[i];
        pixels[i] = (
                ((px      ) & 0xFF000000) | // A
                ((px << 16) & 0x00FF0000) | // R
                ((px      ) & 0x0000FF00) | // G
                ((px >> 16) & 0x000000FF)	// B
        );
    }

    static GLuint textures[1];

    glGenTextures(1, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ((Live2DModelOpenGL*)model)->setTexture(no, textures[0]) ;

    L2DTextureDesc *textureDesc = new L2DTextureDesc(textures[0]);

    env->ReleaseIntArrayElements(array, pixels, 0);
    //env->DeleteGlobalRef(array);
    mid = env->GetMethodID(cls, "close", "(Landroid/graphics/Bitmap;)V");
    env->CallVoidMethod(pngmgr, mid, png);
    //env->DeleteGlobalRef(png);

    return textureDesc;
}

void PlatformManager::log(const char* txt)
{
    UtDebug::print(txt);
}