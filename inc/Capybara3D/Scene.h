#pragma once
#include <memory>
#include <list>

#include "Camera.h"
#include "Canvas.h"
#include "Object.h"
#include <GLFW/glfw3.h>

namespace C3D
{
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
