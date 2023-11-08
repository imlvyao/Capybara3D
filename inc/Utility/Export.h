#pragma once
#ifdef WIN32
    #ifdef C3D_STATIC
        #define C3D_UTILITY_EXPORT 
    #elif C3D_UTILITY_DLL
        #define C3D_UTILITY_EXPORT __declspec(dllexport)
    #else
        #define C3D_UTILITY_EXPORT __declspec(dllimport)
    #endif
#elif __linux__
    #define C3D_UTILITY_EXPORT 
#endif