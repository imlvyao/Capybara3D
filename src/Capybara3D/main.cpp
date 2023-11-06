//main()
//{
//    Scene scene;
//    Camera camera;
//    scene.addObject(camera);
//    Object cow;
//    scene.addObject(cow);
//    cow.addScript<Script>(scriptCow);
//    put(camera.getImageBuffer(0));
//
//    Texture texture;
//    texture.bindBuffer(camera.getImageBuffer(0));
//
//    Camera camera2;
//    camera2.bindTexture(texture,0);
//}

//void main
//{
//    Scene scene1;  //OpenGL程序进程级别，可加模型、相机、画布等
//    Camera camera1;  //program级别，可加Uniform、可加shader, 不/显示模型
//    Shader shader1;
//    camera1.AddShader(shader1);
//    scene1.AddCamera(camera1);
//    Model cow;  //具体模型
//    cow.AddUniform<float>(0.5);
//    Light light1;
//    scene1.AddObject<Model>(cow);
//    scene1.AddObject<Light>(light1);
//    scene1.play();
//
//    Texture tex1;
//    Texture::bind(tex1, scene1.getCamera()->view());
//
//    Canvas canvas1;  //program级别，可加Uniform、可加shader，不显示模型
//    Shader shader2;
//    canvas1.AddUniform<Texture>(tex1);
//    canvas1.AddShader(shader2);
//    scene1.AddCanvas(canvas1);
//
//    Texture tex2;
//    Texture::bind(tex2, scene1.getCanvas1()->view());
//
//    while (tex2.hasBuffer())
//    {
//        saveImage(tex2.getBuffer);
//    }
//}

#include "Scene.h"
int main()
{
    auto scene = std::make_shared<C3D::Scene>();
    auto camera = std::make_shared<C3D::Camera>();
    auto obj = std::make_shared<C3D::Object>();
    scene->addCamera(camera);
    scene->addObject(obj);
    scene->play();
    scene->stop();
}