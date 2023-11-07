#include "Camera.h"
#include <tools/stb_image.h>
#include <tools/filesystem.h>
#include <glm/gtc/matrix_transform.hpp>

namespace C3D
{
    void C3D::Camera::init()
    {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        float yaw = -90.0f;
        float pitch = 0.0f;
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        MovementSpeed = 2.5f; 
        MouseSensitivity = 0.1f;
        Zoom = 45.0f;

        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();

        glEnable(GL_DEPTH_TEST);
        _shader = std::make_shared<Shader>(
            "../../resources/shaders/7.4.camera.vs",
            "../../resources/shaders/7.4.camera.fs");
        _shader->use();
    }

    void Camera::update()
    {
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;

        float lastX = (float)SCR_WIDTH / 2.0;
        float lastY = (float)SCR_HEIGHT / 2.0;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        _shader->use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        _shader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = GetViewMatrix();
        _shader->setMat4("view", view);
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
}