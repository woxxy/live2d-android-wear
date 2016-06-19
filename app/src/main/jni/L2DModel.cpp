#include <string>
#include <sstream>

#include "L2DModel.h"
#include "Live2DModelOpenGL.h"
#include "live2dframework/Live2DFramework.h"

using namespace std;

namespace live2d {
    namespace framework {
        void L2DModel::load(string basePath, string jsonPath) {
            IPlatformManager *pm = Live2DFramework::getPlatformManager();

            modelHomeDir = basePath + "/live2d/haru/";
            string path = modelHomeDir + jsonPath;

            size_t size;
            unsigned char *data = pm->loadBytes(path.c_str(), &size);
            ModelSetting *setting = new ModelSettingJson((const char *) data, (int) size);
            pm->releaseBytes(data);

            init(setting);
        }

        void L2DModel::init(ModelSetting *setting) {
            updating = true;
            initialized = false;

            modelSetting = setting;

            //Live2D Model
            if (strcmp(modelSetting->getModelFile(), "") != 0) {
                string path = modelSetting->getModelFile();
                path = modelHomeDir + path;
                loadModelData(path.c_str());

                int len = modelSetting->getTextureNum();


                for (int i = 0; i < len; i++) {
                    string texturePath = modelSetting->getTextureFile(i);
                    texturePath = modelHomeDir + texturePath;
                    loadTexture(i, texturePath.c_str());
                }
            }

            //Expression
            if (modelSetting->getExpressionNum() > 0) {
                int len = modelSetting->getExpressionNum();
                for (int i = 0; i < len; i++) {
                    string name = modelSetting->getExpressionName(i);
                    string file = modelSetting->getExpressionFile(i);
                    file = modelHomeDir + file;
                    loadExpression(name.c_str(), file.c_str());
                }
            }

            //Physics
            if (strcmp(modelSetting->getPhysicsFile(), "") != 0) {
                string path = modelSetting->getPhysicsFile();
                path = modelHomeDir + path;
                loadPhysics(path.c_str());
            }

            //Pose
            if (strcmp(modelSetting->getPoseFile(), "") != 0) {
                string path = modelSetting->getPoseFile();
                path = modelHomeDir + path;
                loadPose(path.c_str());
            }

            //Layout
            map<string, float> layout;
            modelSetting->getLayout(layout);
            modelMatrix->setupLayout(layout);


            for (int i = 0; i < modelSetting->getInitParamNum(); i++) {
                live2DModel->setParamFloat(modelSetting->getInitParamID(i),
                                           modelSetting->getInitParamValue(i));
            }

            for (int i = 0; i < modelSetting->getInitPartsVisibleNum(); i++) {
                live2DModel->setPartsOpacity(modelSetting->getInitPartsVisibleID(i),
                                             modelSetting->getInitPartsVisibleValue(i));
            }

            live2DModel->saveParam();
            live2DModel->setPremultipliedAlpha(true);

            for (int i = 0; i < modelSetting->getMotionGroupNum(); i++) {
                const char *group = modelSetting->getMotionGroupName(i);
                preloadMotionGroup(group);
            }

            mainMotionMgr->stopAllMotions();

            updating = false;
            initialized = true;
        }

        void L2DModel::preloadMotionGroup(const char group[]) {
            int len = modelSetting->getMotionNum(group);
            for (int i = 0; i < len; i++) {
                stringstream ss;

                //ex) idle_0
                ss << group << "_" << i;

                string name = ss.str();
                string path = modelSetting->getMotionFile(group, i);
                path = modelHomeDir + path;


                loadMotion(name.c_str(), path.c_str());

                const char *voice = modelSetting->getMotionSound(group, i);
                if (strcmp(voice, "") != 0) {
                    string path = voice;
                    path = modelHomeDir + path;


                    //SimpleAudioEngine::getInstance()->preloadEffect(path.c_str());
                }
            }
        }


        void L2DModel::releaseMotionGroup(const char group[]) {
            int len = modelSetting->getMotionNum(group);
            for (int i = 0; i < len; i++) {
                const char *voice = modelSetting->getMotionSound(group, i);
                if (voice != NULL) {
                    string path = voice;
                    path = modelHomeDir + path;

                    //SimpleAudioEngine::getInstance()->unloadEffect(path.c_str());
                }
            }
        }

        void L2DModel::draw() {
            if(mainMotionMgr->isFinished()) {
                mainMotionMgr->startMotion(motions["idle_0"], false);
            } else {
                bool update = mainMotionMgr->updateParam(live2DModel);

                if(!update) {
                    eyeBlink->setParam(live2DModel);
                }
            }

            live2DModel->saveParam();

            live2DModel->update();
            live2DModel->draw();
        }

        void L2DModel::setMatrix(int width, int height) {
            float w = getLive2DModel()->getCanvasWidth();
            float h = getLive2DModel()->getCanvasHeight();
            ((live2d::Live2DModelOpenGL *) getLive2DModel())->setMatrix(modelMatrix->getArray());
        }

    }
}