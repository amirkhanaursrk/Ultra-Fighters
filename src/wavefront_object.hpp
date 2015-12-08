#include "game_node.hpp"
#include "myglutils.h"

class WavefrontObject: public GameNode {
    public:
        WavefrontObject(const char* path);

        void setCamPos(glm::vec3 pos) override;
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
