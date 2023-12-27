//#include <boost/interprocess/shared_memory_object.hpp>
//#include <boost/interprocess/mapped_region.hpp>
//#include <boost/interprocess/sync/interprocess_mutex.hpp>
//#include <boost/thread/thread.hpp>
//#include <iostream>
//
//// ���������ڱ��������ڴ�ķ���
//boost::interprocess::interprocess_mutex mutex;
//
//void writeSharedMemory(const char* message) {
//    using namespace boost::interprocess;
//
//    try {
//        // �򿪹����ڴ����
//        shared_memory_object sharedMemory(open_only, "MySharedMemory", read_write);
//
//        // ӳ�乲���ڴ浽���̵�ַ�ռ�
//        mapped_region region(sharedMemory, read_write);
//
//        // ��ȡ�����ڴ����ʼ��ַ
//        void* sharedMemoryAddress = region.get_address();
//
//        // ������������ȷ���̰߳�ȫ���ʹ����ڴ�
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex);
//
//        // �ڹ����ڴ���д������
//        std::strcpy(static_cast<char*>(sharedMemoryAddress), message);
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//}
//
//void readSharedMemory() {
//    using namespace boost::interprocess;
//
//    try {
//        // �򿪹����ڴ����
//        shared_memory_object sharedMemory(open_only, "MySharedMemory", read_only);
//
//        // ӳ�乲���ڴ浽���̵�ַ�ռ�
//        mapped_region region(sharedMemory, read_only);
//
//        // ��ȡ�����ڴ����ʼ��ַ
//        void* sharedMemoryAddress = region.get_address();
//
//        // ������������ȷ���̰߳�ȫ���ʹ����ڴ�
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex);
//
//        // �ӹ����ڴ��ж�ȡ����
//        std::cout << "Message from shared memory: " << static_cast<const char*>(sharedMemoryAddress) << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//}
//
//int main() {
//    // ���������ڴ����
//    boost::interprocess::shared_memory_object sharedMemory(
//        boost::interprocess::open_or_create, "MySharedMemory", boost::interprocess::read_write);
//
//    // ���ù����ڴ��СΪ100�ֽ�
//    sharedMemory.truncate(100);
//
//    // ����һ��д�߳�
//    //boost::thread writerThread(writeSharedMemory, "Hello, Boost Shared Memory!");
//
//    // ����һ�����߳�
//    boost::thread readerThread(readSharedMemory);
//
//    // �ȴ��߳̽���
//    //writerThread.join();
//    readerThread.join();
//    system("pause");
//    return 0;
//}
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cmath>
#include "ToppleTheTower/Actor.h"
const float PI = 3.14159265359;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class DrawTool
{
public:
    DrawTool()
    {
        m_canvasColor = glm::vec3(1, 0, 0);
    }

    void setWindowWidthHeight(const double& w, const double& h)
    {
        m_windowWidth = w;
        m_windowHeight = h;
    }
    double getWindowW() 
    {
        return m_windowWidth;
    }
    double getWindowH() 
    { 
        return m_windowHeight;
    }
    void setCanvasWidthHeight(const double& w, const double& h)
    {
        m_canvasWidth = w;
        m_canvasHeight = h;
    }
    void setCanvasUnitToWindowWidth(const double& unitToWindowWidth)
    {
        m_unitToWindowWidth = unitToWindowWidth;
    }

    // x,yΪ�������꣬����Ϊԭ��
    void drawCanvas(const double& x, const double& y)
    {
        m_canvasX = x;
        m_canvasY = y;
        glColor3f(m_canvasColor.x, m_canvasColor.y, m_canvasColor.z);
        double unit = m_unitToWindowWidth * m_windowWidth;
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-m_canvasWidth*0.5* unit, -m_canvasHeight * 0.5 * unit);
        glVertex2f(m_canvasWidth * 0.5 * unit, -m_canvasHeight * 0.5 * unit);
        glVertex2f(m_canvasWidth * 0.5 * unit, m_canvasHeight * 0.5 * unit);
        glVertex2f(-m_canvasWidth * 0.5 * unit, m_canvasHeight * 0.5 * unit);
        glEnd();
        glPopMatrix();
    }

    // ���ƾ��Σ�x,yΪ�������꣬��������Ϊԭ�㣬���ȵ�λΪ��Ե�λ
    void drawRectangle(
        const double& x, const double& y, 
        const double& w, const double& h, 
        const bool& isEmpty = true,
        const glm::vec3& color = glm::vec3(1,1,1))
    {
        double unit = m_unitToWindowWidth * m_windowWidth;
        glColor3f(color.x, color.y, color.z);
        glPushMatrix();
        glTranslatef(m_canvasX+x* unit, m_canvasY+y* unit, 0.0f);
        if (isEmpty)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2f(-w * 0.5 * unit, -h * 0.5 * unit);
            glVertex2f(w * 0.5 * unit, -h * 0.5 * unit);
            glVertex2f(w * 0.5 * unit, h * 0.5 * unit);
            glVertex2f(-w * 0.5 * unit, h * 0.5 * unit);
            glEnd();
        }
        else
        {
            glBegin(GL_QUADS);
            glVertex2f(-w * 0.5 * unit, -h * 0.5 * unit);
            glVertex2f(w * 0.5 * unit, -h * 0.5 * unit);
            glVertex2f(w * 0.5 * unit, h * 0.5 * unit);
            glVertex2f(-w * 0.5 * unit, h * 0.5 * unit);
            glEnd();
        }

        glPopMatrix();
    }
    // ����Բ�Σ�x,yΪ�������꣬��������Ϊԭ�㣬���ȵ�λΪ��Ե�λ
    void drawCircle(
        const double& x, const double& y,
        const double& r,
        const bool& isEmpty = true,
        const glm::vec3& color = glm::vec3(1, 1, 1),
        const int& segments = 50)
    {
        double unit = m_unitToWindowWidth * m_windowWidth;
        glColor3f(color.x, color.y, color.z);
        glPushMatrix();
        glTranslatef(m_canvasX + x * unit, m_canvasY + y * unit, 0.0f);
        if (isEmpty)
        {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segments; ++i) {
                float theta = 2.0 * PI * i / segments;
                float x = r * cos(theta);
                float y = r * sin(theta);
                glVertex2f(x, y);
            }
            glEnd();
        }
        else
        {
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0, 0.0); // ���ĵ�
            for (int i = 0; i <= segments; ++i) {
                float theta = 2.0 * PI * i / segments;
                float x = r * cos(theta);
                float y = r * sin(theta);
                glVertex2f(x, y);
            }
            glEnd();
        }

        glPopMatrix();
    }
private:
    double m_windowWidth;
    double m_windowHeight;

    double m_canvasWidth;
    double m_canvasHeight;
    double m_canvasX;
    double m_canvasY;

    double m_unitToWindowWidth;

    glm::vec3 m_canvasColor;
};

// ����Ŀ��֡��
const int targetFPS = 30;

// ����֡����ر���
double currentTime = 0.0;
double previousTime = 0.0;
double sumTime = 0.0;
long sumFrameCount = 0;
// ����֡��
void updateFrameRate() {
    currentTime = glfwGetTime();
    double frameTime = 1.0 / targetFPS;

    // ������Ҫ�ȴ���ʱ��
    double elapsedTime = currentTime - previousTime;
    double sleepTime = frameTime - elapsedTime;

    // �����Ҫ�ȴ��������˯��
    if (sleepTime > 0.0)
    {
        glfwWaitEventsTimeout(sleepTime);
    }

    double previousTimeT = glfwGetTime();

    sumTime += previousTimeT - previousTime;
    previousTime = previousTimeT;

    sumFrameCount++;
    if (sumTime>=1.0)
    {
        //std::cout << "FPS:" << sumFrameCount * 1.0 / sumTime << std::endl;
        sumTime = 0.0;
        sumFrameCount = 0;
    }
}

DrawTool drawTool;


boost::interprocess::interprocess_mutex mutex;
using namespace boost::interprocess;
int main() 
{

    if (!glfwInit()) {
        return -1;
    }

    {
        drawTool.setWindowWidthHeight(800, 1300);
        drawTool.setCanvasWidthHeight(100, 160);
        drawTool.setCanvasUnitToWindowWidth(1.0 / 150.0);
    }

    GLFWwindow* window = glfwCreateWindow(drawTool.getWindowW(), drawTool.getWindowH(), "GLFW Rectangle Example", NULL, NULL);

    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(
            -drawTool.getWindowW() * 0.5,
            drawTool.getWindowW() * 0.5,
            -drawTool.getWindowH() * 0.5,
            drawTool.getWindowH() * 0.5, -1.0, 1.0); // ��������ͶӰ
        glMatrixMode(GL_MODELVIEW);


        TransData receivedDataObject;
        {
            const char* sharedMemoryName = "MySharedMemory";
            const char* mutexName = "MyMutex";
            const std::size_t sharedMemorySize = 65536;
            try {
                boost::interprocess::named_mutex namedMutex(boost::interprocess::open_or_create, mutexName);
                boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(namedMutex);
                boost::interprocess::managed_shared_memory segment(boost::interprocess::open_or_create, sharedMemoryName, sharedMemorySize);

                // Retrieve the shared memory buffer
                char* sharedMemoryBuffer = segment.find<char>("SharedMemoryBuffer").first;

                // Get the size of the serialized data
                std::size_t dataSize = segment.find<char>("SharedMemoryBuffer").second;

                // Deserialize the data from the shared memory buffer
                std::string receivedData(sharedMemoryBuffer, sharedMemoryBuffer + dataSize);


                std::stringstream receivedStream(receivedData);
                //boost::archive::text_iarchive ia(receivedStream);
                boost::archive::binary_iarchive ia(receivedStream);
                ia >> receivedDataObject;

                std::cout << "Received MyData:" << receivedDataObject.m_canvas.m_h << std::endl;
                // Access and use the deserialized data
                //std::cout << "Received MyData: " << receivedDataObject.intValue << " " << receivedDataObject.doubleValue << " " << receivedDataObject.stringValue << std::endl;

            }
            catch (const std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
            }
        }
        if (receivedDataObject.m_canvas.m_h>0)
        {
            drawTool.setCanvasWidthHeight(receivedDataObject.m_canvas.m_w, receivedDataObject.m_canvas.m_h);
            drawTool.drawCanvas(receivedDataObject.m_canvas.m_x, receivedDataObject.m_canvas.m_y);
        }

        {
            for (Tower& tower: receivedDataObject.m_enemy.getTower())
            {
                drawTool.drawCircle(tower.getXY().x, tower.getXY().y, tower.getCollisionRadius(), false, glm::vec3(0, 1, 1));
                drawTool.drawCircle(tower.getXY().x, tower.getXY().y, tower.getAttackRadius(), true, glm::vec3(0, 1, 1));
            }

            for (Footman& footman : receivedDataObject.m_enemy.getFootman())
            {
                drawTool.drawCircle(footman.getXY().x, footman.getXY().y, footman.getCollisionRadius(), false, glm::vec3(0, 1, 1));
                drawTool.drawCircle(footman.getXY().x, footman.getXY().y, footman.getAttackRadius(), true, glm::vec3(0, 1, 1));
            }
        }

        {
            for (Tower& tower : receivedDataObject.m_self.getTower())
            {
                drawTool.drawCircle(tower.getXY().x, tower.getXY().y, tower.getCollisionRadius(), false, glm::vec3(0, 1, 0));
                drawTool.drawCircle(tower.getXY().x, tower.getXY().y, tower.getAttackRadius(), true, glm::vec3(0, 1, 0));
            }

            for (Footman& footman : receivedDataObject.m_self.getFootman())
            {
                drawTool.drawCircle(footman.getXY().x, footman.getXY().y, footman.getCollisionRadius(), false, glm::vec3(0, 1, 0));
                drawTool.drawCircle(footman.getXY().x, footman.getXY().y, footman.getAttackRadius(), true, glm::vec3(0, 1, 0));
            }
        }

        glfwSwapBuffers(window);

        updateFrameRate();

        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    drawTool.setWindowWidthHeight(width, height);
}