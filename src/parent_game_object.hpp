#pragma once 

#include <vector>

#include "game_object.hpp"

class ParentGameObject: public GameObject {
    public:
        void setVPM(glm::mat4 VPM) override;
        void render(float interp) override;
        void update(double step) override;
        void addChild(GameObject* object);
    
    protected:
        std::vector<GameObject*> children;
        glm::mat4 VPM;
    
    private:
        std::vector<GameObject*> newChildren;
};