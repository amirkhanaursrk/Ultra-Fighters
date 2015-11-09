#pragma once

#include "game_object.hpp"

class Cube: public GameObject {
    public:
        void setVPM(glm::mat4 VPM) override;
        void setup() override;
        void update(double step) override;
        void render(float interp) override;
    
    private:
        glm::mat4* MVP;
        GLuint vao;
        GLuint program;
<<<<<<< HEAD
=======
        int length;
>>>>>>> SPC-Week-Branch-2
};
