#include "L2DModel.h"
#include "Live2DModelOpenGL.h"

void L2DModel::draw()
{
    eyeBlink->setParam(getLive2DModel());
    getLive2DModel()->update();
    getLive2DModel()->draw();
}

void L2DModel::setMatrix(int width, int height)
{
    float w = getLive2DModel()->getCanvasWidth();
    float h = getLive2DModel()->getCanvasHeight();
    modelMatrix->scale(1.0f / w * 3.0f, -1.0f / w * 3.0f * ((float) width / height));
    modelMatrix->translate(-1.5f, 1.0f);
    ((live2d::Live2DModelOpenGL *)getLive2DModel())->setMatrix(modelMatrix->getArray());
}
