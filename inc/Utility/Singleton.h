#pragma once

#include <iostream>
#include <mutex>
#include "Export.h"


class C3D_UTILITY_EXPORT SingletonBase {
private:
    static std::mutex mutex;

protected:
    // 使用局部静态变量确保线程安全的单例实例创建
    static SingletonBase*& getInstanceInternal() {
        static SingletonBase* instance = nullptr;
        return instance;
    }
    SingletonBase(){}
public:
    virtual ~SingletonBase() = default;

    // 获取单例实例的方法
    static SingletonBase& getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (getInstanceInternal() == nullptr) {
            getInstanceInternal() = new SingletonBase();  // 在实际使用中可能需要替换为具体的单例类的创建方法
        }
        return *getInstanceInternal();
    }

    // 阻止拷贝构造函数和赋值运算符
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
};