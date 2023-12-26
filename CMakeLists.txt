# 为了使用nuget最低版本3.20
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
# compile options
if(WIN32)
    # 字符集为Unicode
    #add_compile_definitions(UNICODE)
    #add_compile_definitions(_UNICODE)
    #add_compile_definitions(_TURN_OFF_PLATFORM_STRING)
    # OpenGL GLAD
    add_compile_definitions(GLAD_GLAPI_EXPORT)
    # 是否优化
    add_compile_options(-fno-elide-constructors)

elseif(UNIX)
    #add_compile_definitions(UNICODE)
    #add_compile_definitions(_UNICODE)
    #add_compile_definitions(_TURN_OFF_PLATFORM_STRING)
    #add_compile_options(-fPIC)
    #add_compile_options(-ltcmalloc)
    #add_compile_options(-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free)
endif()

if(WIN32)
    message(NOTICE "System Type:Windows!")
    #set(CMAKE_SYSTEM_VERSION 10)
    #set(VCPKG_TARGET_ARCHITECTURE x64)
    set(VCPKG_CRT_LINKAGE dynamic)
    set(VCPKG_LIBRARY_LINKAGE dynamic)
    set(VCPKG_PLATFORM_TOOLSET "v143")
    set(VCPKG_DEP_INFO_OVERRIDE_VARS "v143")
    # C++标准版本
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    #关闭优化
    set(CMAKE_CXX_FLAGS "-fno-elide-constructors ${CMAKE_CXX_FLAGS}")
    # 设置 C++ 编译器标志
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0") # -O0 表示关闭优化

elseif(UNIX)
    message(NOTICE "System Type:UNIX or Linux!")
    #set(CMAKE_C_COMPILER "/usr/bin/clang")
    #set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    #add_compile_definitions(stdlib=libc++)
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/gcc")
    # C++标准版本
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

endif()

project(Capybara3D)

#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/config" DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/doc" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION ${CMAKE_BINARY_DIR})

# 加入子路径
add_subdirectory(src)