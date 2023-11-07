#pragma once

#include <glm/glm.hpp>

#include "Component.h"

namespace C3D
{
    class Transform : public Component
    {
    public:
        void setRotation(const glm::quat& rotation);
        void setPosition(const glm::vec3& position);
    private:
        glm::mat4 _mat4;
    };
}
