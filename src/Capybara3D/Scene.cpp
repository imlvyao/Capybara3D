#include "Scene.h"
#include "Utility/Timer.h"

C3D::Scene::Scene()
{
    init();
}

C3D::Scene::~Scene()
{

}
void C3D::Scene::play()
{
    while (!glfwWindowShouldClose(_window.get()))
    {
        auto t1 = C3D::Timer::nowCpuTime();
        for (auto& camera : _cameras)
        {
            camera->update();
            for (size_t i = 0; i < 1000000; i++)
            {
                for (auto& obj : _objects)
                {
                    obj->update(camera->getShader());
                }
            }
        }
        glfwSwapBuffers(_window.get());
        glfwPollEvents();
        auto t4 = C3D::Timer::nowCpuTime();
        std::cout << "frame time:" << t4 - t1 << std::endl;
    }
}

//void C3D::Scene::play()
//{
//    while (!glfwWindowShouldClose(_window.get()))
//    {
//        C3D::Timer timer;
//        timer.startGpuTimer();
//        auto t1 = C3D::Timer::nowCpuTime();
//        for (auto& camera : _cameras)
//        {
//            camera->update();
//
//            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//            float angle = 20.0f * 1;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            camera->getShader()->setMat4("model", model);
//
//            for (auto& obj : _objects)
//            {
//                glActiveTexture(GL_TEXTURE0);
//                glBindTexture(GL_TEXTURE_2D, obj->texture1);
//                glActiveTexture(GL_TEXTURE1);
//                glBindTexture(GL_TEXTURE_2D, obj->texture2);
//
//                glBindVertexArray(obj->VAO);
//
//                for (size_t i = 0; i < 1000000; i++)
//                {
//                    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//                    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//                    float angle = 20.0f * 1+i%10;
//                    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//                    camera->getShader()->setMat4("model", model);
//                    glActiveTexture(GL_TEXTURE0);
//                    (i%2==0)? glBindTexture(GL_TEXTURE_2D, obj->texture1) :glBindTexture(GL_TEXTURE_2D, obj->texture2);
//                    glActiveTexture(GL_TEXTURE1);
//                    (i % 2 == 0) ? glBindTexture(GL_TEXTURE_2D, obj->texture2): glBindTexture(GL_TEXTURE_2D, obj->texture1);
//                    obj->update(camera->getShader());
//                }
//                for (size_t i = 0; i < 1000000; i++)
//                {
//                    //obj->update(camera->getShader());
//                }
//            }
//        }
//        auto t2 = C3D::Timer::nowCpuTime();
//        auto time = timer.endGpuTimer();
//        std::cout << "cpu time:" << t2-t1 << std::endl;
//        std::cout << "gpu time:" << time << std::endl;
//        auto t3 = C3D::Timer::nowCpuTime();
//        glfwSwapBuffers(_window.get());
//        auto t4 = C3D::Timer::nowCpuTime();
//        glfwPollEvents();
//        std::cout << "SwapBuffer time:" << t4 - t3 << std::endl;
//
//        std::cout << "frame time:" << t4 - t1 << std::endl;
//    }
//}

void C3D::Scene::stop()
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

    for (auto& camera : _cameras)
    {
        auto uniforms = t->getUniforms();
        for (const auto& uniform : uniforms)
        {
            camera->getShader()->setInt(uniform.first, uniform.second);
        }
    }
}

void C3D::Scene::addCamera(const std::shared_ptr<Camera> t)
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
