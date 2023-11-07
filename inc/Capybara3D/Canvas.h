#pragma once
#include <memory>
#include <list>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <tools/shader_m.h>

namespace C3D
{
    class ObjectBase
    {
    public:

    private:


    };

    class Object :public ObjectBase
    {
    public:
        void init();
        void update(std::shared_ptr<Shader> shader);

        std::map<std::string, int>& getUniforms() { return _intUniforms; }
        unsigned int VBO, VAO, texture1, texture2;
    private:
        std::map<std::string, int> _intUniforms;
    };

    class Camera :public ObjectBase
    {
    public:
        void init();
        std::shared_ptr<Shader> getShader() { return _shader; }
        void update();
        glm::mat4 GetViewMatrix();

    private:
        void updateCameraVectors()
        {
            // calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }

    private:
        std::shared_ptr<Shader> _shader;
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

    };

    class Canvas :public Camera
    {
    public:
        void init();

    private:


    };

    class Scene
    {
    public:
        Scene();
        virtual ~Scene();

        void play();
        void stop();

        void addObject(const std::shared_ptr<Object> t);
        void addCamera(const std::shared_ptr<Camera> t);

    private:
        void init();
    private:

        std::list<std::shared_ptr<Object>> _objects;
        std::list<std::shared_ptr<Camera>> _cameras;
        std::list<std::shared_ptr<Canvas>> _canvass;

        std::shared_ptr<GLFWwindow> _window;
    };

}
