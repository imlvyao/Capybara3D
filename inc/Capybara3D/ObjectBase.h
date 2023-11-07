#pragma once
#include <memory>
#include <list>

#include "Component.h"

namespace C3D
{
    class ObjectBase
    {
    public:
        template<class T>
        void addComponent(std::shared_ptr<T> component)
        {
            auto temp = std::dynamic_pointer_cast<Component>(component);
            if (temp != nullptr)
            {
                _compents.push_back(temp);
            }
            else
            {
                throw std::runtime_error("the parameter is not of <Component> type!");
            }
        }
    private:

        std::list<std::shared_ptr<Component>> _compents;
    };
}
