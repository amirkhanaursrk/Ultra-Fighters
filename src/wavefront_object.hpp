#include "game_object.hpp"

#include "myglutils.h"

class WavefrontObject: public GameObject {
    public:
        WavefrontObject(const char* path);
        void setVPM(glm::mat4 VPM) override;
        void setup() override;
        void update(double step) override {}
        void render(float interp) override;

    private:
        glm::mat4* MVP;
        GLuint vao;
        GLuint program;
        int length;
        const char* path;
};
