#pragma once
#include <memory>
#include <map>

#include <ObjectBase.h>
#include <tools/shader_m.h>

namespace C3D
{
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
}
