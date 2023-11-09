#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Timer.h"

long C3D::Timer::nowCpuTime()
{
    auto time = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
    return ms.count();
}

void C3D::Timer::startGpuTimer()
{
    _gpuTimerQuery = 0;
    glGenQueries(1, &_gpuTimerQuery);
    glBeginQuery(GL_TIME_ELAPSED, _gpuTimerQuery);
}

long C3D::Timer::endGpuTimer()
{
    glEndQuery(GL_TIME_ELAPSED);
    GLuint available = 0;
    while (!available) {
        glGetQueryObjectuiv(_gpuTimerQuery, GL_QUERY_RESULT_AVAILABLE, &available);
    }

    GLuint64 elapsed_time;
    glGetQueryObjectui64v(_gpuTimerQuery, GL_QUERY_RESULT, &elapsed_time);
    glDeleteQueries(1, &_gpuTimerQuery);

    return elapsed_time / 1000000.0;
}
