#include "Global.h"
#include "live2dframework/L2DBaseModel.h"
#include "ModelSettingJson.h"

namespace live2d
{
    namespace framework {
        class L2DModel : public L2DBaseModel {
        private:
            ModelSetting *modelSetting;
            string modelHomeDir;
        public:
            void draw();
            void setMatrix(int width, int height);
            void load(string basePath, string path);

            void init(ModelSetting *setting);

            void preloadMotionGroup(const char *group);

            void releaseMotionGroup(const char *group);
        };

    }
}