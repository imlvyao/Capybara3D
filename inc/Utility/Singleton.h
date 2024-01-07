#pragma once

#include <iostream>
#include <mutex>
#include "Export.h"


class C3D_UTILITY_EXPORT SingletonBase {
private:
    static std::mutex mutex;

protected:
    // ʹ�þֲ���̬����ȷ���̰߳�ȫ�ĵ���ʵ������
    static SingletonBase*& getInstanceInternal() {
        static SingletonBase* instance = nullptr;
        return instance;
    }
    SingletonBase(){}
public:
    virtual ~SingletonBase() = default;

    // ��ȡ����ʵ���ķ���
    static SingletonBase& getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (getInstanceInternal() == nullptr) {
            getInstanceInternal() = new SingletonBase();  // ��ʵ��ʹ���п�����Ҫ�滻Ϊ����ĵ�����Ĵ�������
        }
        return *getInstanceInternal();
    }

    // ��ֹ�������캯���͸�ֵ�����
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
};