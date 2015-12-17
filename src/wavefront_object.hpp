#include "myglutils.h"
#include "game_node.hpp"

class WavefrontObject: public GameNode {
    public:
        WavefrontObject(const char* path);

        bool setup() override;
        void update(double step) override {}
        void render(float interp) override;

    private:
        GLuint vao;
        GLuint program;
        int length;
        const char* path;
};
