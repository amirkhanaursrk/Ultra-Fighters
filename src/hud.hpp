#include "myglutils.h"
#include "game_node.hpp"

class HUD: public GameNode {
public:
    bool setup() override;
    void render(float interp) override;
    void update(double step) override;

private:
    GLuint vao;
    GLuint program;
    int vertices;
};