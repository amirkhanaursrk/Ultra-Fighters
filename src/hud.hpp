#include "game_node.hpp"
#include "myglutils.h"

class HUD: public GameNode {
public:
    void setCamPos(glm::vec3 pos) override {}
    void setVPM(glm::mat4 VPM) override {}
    void setup() override;
    void render(float interp) override;
    void update(double step) override {}

private:
    GLuint vao;
    GLuint program;
    int vertices;
};