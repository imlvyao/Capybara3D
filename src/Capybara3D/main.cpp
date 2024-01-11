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
//    Scene scene1;  //OpenGL������̼��𣬿ɼ�ģ�͡������������
//    Camera camera1;  //program���𣬿ɼ�Uniform���ɼ�shader, ��/��ʾģ��
//    Shader shader1;
//    camera1.AddShader(shader1);
//    scene1.AddCamera(camera1);
//    Model cow;  //����ģ��
//    cow.AddUniform<float>(0.5);
//    Light light1;
//    scene1.AddObject<Model>(cow);
//    scene1.AddObject<Light>(light1);
//    scene1.play();
//
//    Texture tex1;
//    Texture::bind(tex1, scene1.getCamera()->view());
//
//    Canvas canvas1;  //program���𣬿ɼ�Uniform���ɼ�shader������ʾģ��
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

//#include "Scene.h"
//#include "Transform.h"
//int main()
//{
//    auto scene = std::make_shared<C3D::Scene>();
//    auto camera = std::make_shared<C3D::Camera>();
//    auto obj = std::make_shared<C3D::Object>();
//    auto trans1 = std::make_shared<C3D::Transform>();
//    obj->addComponent<C3D::Transform>(trans1);
//    scene->addCamera(camera);
//    scene->addObject(obj);
//    scene->play();
//    scene->stop();
//}

//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
////#define STB_IMAGE_IMPLEMENTATION
//#include <tools/stb_image.h>
//
//const char* vertexShaderSource = R"(
//    #version 330 core
//    layout (location = 0) in vec3 aPos;
//    layout (location = 1) in vec2 aTexCoord;
//
//    out vec2 TexCoord;
//
//    void main()
//    {
//        gl_Position = vec4(aPos, 1.0);
//        TexCoord = aTexCoord;
//    }
//)";
//
//const char* fragmentShaderSource = R"(
//    #version 330 core
//    in vec2 TexCoord;
//    out vec4 FragColor;
//
//    uniform sampler2D myTexture;
//    uniform sampler2DMS myMultisampleTexture;
//
//    void main()
//    {
//        ivec2 texCoord = ivec2(TexCoord * textureSize(myTexture, 0));
//        vec4 texel = texelFetch(myMultisampleTexture, texCoord, 0);
//        FragColor = texel;
//        FragColor = vec4(1,0,0,1);
//    }
//)";
//
//int main()
//{
//    // ��ʼ��GLFW
//    if (!glfwInit())
//    {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return -1;
//    }
//
//    // ����OpenGL�汾Ϊ3.3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//    // ��������
//    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Multisample Texture Example", nullptr, nullptr);
//    if (!window)
//    {
//        std::cerr << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    // ��ʼ��GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cerr << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // �����ӿ�
//    glViewport(0, 0, 800, 600);
//
//    // �����������ɫ������
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    GLuint shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    glUseProgram(shaderProgram);
//
//    // ������ͼ
//    int width, height, channels;
//    stbi_set_flip_vertically_on_load(true); // ��תͼƬ��y��
//    unsigned char* textureData = stbi_load("D:/OSGBuild/data/OpenSceneGraph-Data/Images/skymap.jpg", &width, &height, &channels, 0);
//    if (!textureData)
//    {
//        std::cerr << "Failed to load texture" << std::endl;
//        return -1;
//    }
//
//    // ������������
//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    // �����������
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    stbi_image_free(textureData);
//
//    // �������ز�������
//    GLuint multisampleTexture;
//    glGenTextures(1, &multisampleTexture);
//    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multisampleTexture);
//
//    int samples = 4;
//    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA, width, height, GL_TRUE);
//
//    // ����֡�������FBO��
//    GLuint framebuffer;
//    glGenFramebuffers(1, &framebuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//    // �����ز��������ӵ�FBO
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multisampleTexture, 0);
//
//    // ���֡�����Ƿ�����
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//    {
//        std::cerr << "Framebuffer is not complete" << std::endl;
//        return -1;
//    }
//
//    // ���ö�������
//    float vertices[] = {
//        // λ��            // ��������
//         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
//         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//    };
//
//    // �������󶨶��㻺�����
//    GLuint VBO, VAO;
//    glGenBuffers(1, &VBO);
//    glGenVertexArrays(1, &VAO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // ���Ӷ�������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // ���VAO��VBO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    // ��Ⱦѭ��
//    while (!glfwWindowShouldClose(window))
//    {
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // ��FBO
//        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//        // ʹ�ö��ز������������Ⱦ
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glUniform1i(glGetUniformLocation(shaderProgram, "myTexture"), 0);
//
//        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//
//        // ���FBO
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        // ���Ƶ���Ļ
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multisampleTexture);
//        glUniform1i(glGetUniformLocation(shaderProgram, "myMultisampleTexture"), 0);
//
//        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//
//        // ����������������¼�
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // ������Դ
//    glDeleteTextures(1, &texture);
//    glDeleteTextures(1, &multisampleTexture);
//    glDeleteBuffers(1, &VBO);
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    glDeleteProgram(shaderProgram);
//    glDeleteFramebuffers(1, &framebuffer);
//
//    glfwTerminate();
//
//    return 0;
//}

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
////#define STB_IMAGE_IMPLEMENTATION
//#include <tools/stb_image.h>
//#include <cstdlib>  // ������ͷ�ļ�
//
//GLuint framebuffer;
//GLuint texture;
//int width = 800;
//int height = 600;
//GLFWwindow* window;
//
//void errorCallback(int error, const char* description) {
//    fprintf(stderr, "Error: %s\n", description);
//}
//
//void initialize(GLFWwindow* window) {
//    // Make the window's context current
//    glfwMakeContextCurrent(window);
//
//    // Initialize GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        fprintf(stderr, "Failed to initialize GLAD\n");
//        exit(EXIT_FAILURE);
//    }
//
//    // Enable multisampling
//    glEnable(GL_MULTISAMPLE);
//
//    // Create framebuffer
//    glGenFramebuffers(1, &framebuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//    // Load image using stb_image and create multisample texture
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
//
//    int channels;
//    unsigned char* image = stbi_load("D:/OSGBuild/data/OpenSceneGraph-Data/Images/forestWall.png", &width, &height, &channels, STBI_rgb_alpha);
//    if (!image) {
//        fprintf(stderr, "Failed to load image\n");
//        exit(EXIT_FAILURE);
//    }
//
//    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, width, height, GL_TRUE);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);
//
//    stbi_image_free(image);
//
//    // Check framebuffer status
//    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//    if (status != GL_FRAMEBUFFER_COMPLETE) {
//        fprintf(stderr, "Framebuffer is not complete\n");
//        exit(EXIT_FAILURE);
//    }
//
//    // Unbind framebuffer
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void render(GLFWwindow* window) {
//    // Bind framebuffer
//    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//    // Clear the framebuffer
//    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // Your rendering code goes here
//
//    // Unbind framebuffer
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // Blit multisample texture to the default framebuffer
//    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // Swap front and back buffers
//    glfwSwapBuffers(window);
//
//    // Poll for and process events
//    glfwPollEvents();
//}
//
//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        fprintf(stderr, "Failed to initialize GLFW\n");
//        exit(EXIT_FAILURE);
//    }
//
//    // Set GLFW error callback
//    glfwSetErrorCallback(errorCallback);
//
//    // Create a windowed mode window and its OpenGL context
//    window = glfwCreateWindow(width, height, "Multisample Texture Example", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//
//    // Make the window's context current
//    glfwMakeContextCurrent(window);
//
//    // Initialize GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        fprintf(stderr, "Failed to initialize GLAD\n");
//        exit(EXIT_FAILURE);
//    }
//
//    // ... (����ܻ���Ҫ����һЩOpenGL״̬��������Ȳ��Ե�)
//
//    initialize(window);
//
//    // Loop until the user closes the window
//    while (!glfwWindowShouldClose(window)) {
//        // Render
//        render(window);
//    }
//
//    // Terminate GLFW
//    glfwTerminate();
//
//    return 0;
//}

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Shader������غ���
unsigned int loadShader(const char* source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
    }

    return shader;
}

// Shader�������Ӻ���
unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    unsigned int vertexShader = loadShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = loadShader(fragmentSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    // ��ʼ��glfw
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    // ����glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ��������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Multi-sampling and Post-processing", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ���õ�ǰ������
    glfwMakeContextCurrent(window);

    // ��ʼ��glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD initialization failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ���ز�������
    glEnable(GL_MULTISAMPLE);

    // ���������������VAO���Ͷ��㻺�����VBO������������
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // ��VAO��VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // ���������εĶ�������
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // ���������ݸ��Ƶ�������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ���Ӷ�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ���VAO��VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ��д�����ζ�����ɫ����Ƭ����ɫ��Դ��
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    // ������������������ɫ������
    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // ������ɫ��Դ��
    const char* postProcessingVertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        out vec2 TexCoords;
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            TexCoords = (aPos + 1.0) / 2.0;
        }
    )";

    const char* postProcessingFragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoords;
    out vec4 FragColor;
    uniform sampler2DMS screenTexture; // ʹ�� sampler2DMS
    void main() {
        // ��ʼ����ɫΪ��ɫ
        vec4 color = vec4(0.0);

        // ��ÿ���������в���������
        for (int i = 0; i < 4; ++i) {
            color += texelFetch(screenTexture, ivec2(TexCoords * textureSize(screenTexture)), i);
        }

        // ȡƽ��ֵ
        color /= 4.0;

        FragColor = color;
    }
)";

    // ���������������ɫ������
    unsigned int postProcessingShaderProgram = createShaderProgram(postProcessingVertexShaderSource, postProcessingFragmentShaderSource);

    // ����֡�������FBO��
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // �����������������丽�ӵ�֡���������
    unsigned int textureColorBufferMultiSampled;
    glGenTextures(1, &textureColorBufferMultiSampled);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, 800, 600, GL_TRUE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);

    // ���֡����������
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer is not complete!" << std::endl;
    }

    // ���֡����
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ����������εĶ�������
    float postProcessingVertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

    // ����������εĶ����������VAO���Ͷ��㻺�����VBO��
    unsigned int postProcessingVAO, postProcessingVBO;
    glGenVertexArrays(1, &postProcessingVAO);
    glGenBuffers(1, &postProcessingVBO);

    // �󶨺���VAO��VBO
    glBindVertexArray(postProcessingVAO);
    glBindBuffer(GL_ARRAY_BUFFER, postProcessingVBO);

    // ��������εĶ������ݸ��Ƶ�������
    glBufferData(GL_ARRAY_BUFFER, sizeof(postProcessingVertices), postProcessingVertices, GL_STATIC_DRAW);

    // ���Ӻ���������
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ������VAO��VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ��ѭ��
    while (!glfwWindowShouldClose(window)) {
        // ��Ⱦ��һ�������ز��������ε�FBO
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ��Ⱦ�ڶ�����������ε���Ļ
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glUseProgram(postProcessingShaderProgram);
        glBindVertexArray(postProcessingVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
        glUniform1i(glGetUniformLocation(postProcessingShaderProgram, "screenTexture"), 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // �������岢����¼�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ������Դ
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &postProcessingVAO);
    glDeleteBuffers(1, &postProcessingVBO);
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &textureColorBufferMultiSampled);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(postProcessingShaderProgram);

    // ��ֹglfw
    glfwTerminate();

    return 0;
}
