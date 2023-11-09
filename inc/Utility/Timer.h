#pragma once

#include "Export.h"

namespace C3D
{
    class C3D_UTILITY_EXPORT Timer
    {
    public:
        static long nowCpuTime();

        void startGpuTimer();
        long endGpuTimer();
    private:
        unsigned int _gpuTimerQuery;
    };
}