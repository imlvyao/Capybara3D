#include "Scene.h"

namespace C3D
{
    C3D::Scene::Scene()
    {
        init();
    }

    Scene::~Scene()
    {

    }

    void C3D::Scene::play()
    {
        while (!glfwWindowShouldClose(_window.get()))
        {
            for (auto& camera: _cameras)
            {
                camera->update();
                for (auto& obj : _objects)
                {
                    obj->update(camera->getShader());
                }
            }
            glfwSwapBuffers(_window.get());
            glfwPollEvents();
        }
    }

    void Scene::stop()
    {
        for (auto& objs : _objects)
        {
            glDeleteVertexArrays(1, &objs->VAO);
            glDeleteBuffers(1, &objs->VBO);
        }
        //glfwTerminate();
    }

    void C3D::Scene::addObject(const std::shared_ptr<Object> t)
    {
        _objects.push_back(t);
        t->init();

        for (auto& camera:_cameras)
        {
            auto uniforms = t->getUniforms();
            for (const auto& uniform:uniforms)
            {
                camera->getShader()->setInt(uniform.first,uniform.second);
            }
        }
    }

    void Scene::addCamera(const std::shared_ptr<Camera> t)
    {
        _cameras.push_back(t);
        t->init();

        for (auto& objs : _objects)
        {
            auto uniforms = objs->getUniforms();
            for (const auto& uniform : uniforms)
            {
                t->getShader()->setInt(uniform.first, uniform.second);
            }
        }
    }

    void C3D::Scene::init()
    {
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;

        float lastX = (float)SCR_WIDTH / 2.0;
        float lastY = (float)SCR_HEIGHT / 2.0;
        //TODO 都放到单独线程，或协程
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = std::shared_ptr<GLFWwindow>
            (glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL));
        if (_window.get() == NULL)
        {
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(_window.get());

        glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            return;
        }
    }
}