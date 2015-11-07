#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/mat4x4.hpp>

#include "loop.hpp"

class GameObject : public LoopListener {
public:
    virtual void setVPM(glm::mat4 VPM) = 0; // View Projection Matrix
};

#endif
