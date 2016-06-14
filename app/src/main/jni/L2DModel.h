#include "live2dframework/L2DBaseModel.h"

class L2DModel : public live2d::framework::L2DBaseModel
{
public:
    void draw();
    void setMatrix(int width, int height);
};