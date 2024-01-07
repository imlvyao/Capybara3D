#pragma once
#include <iostream>
#include <mutex>
#include <map>
#include <memory>

#include <Object.h>

class Director
{

private:
    // ʹ�þֲ���̬����ȷ���̰߳�ȫ�ĵ���ʵ������
    static Director*& getInstanceInternal()
    {
        static Director* instance = nullptr;
        return instance;
    }
    Director() 
    {
    }

public:
    virtual ~Director() = default;

    // ��ȡ����ʵ���ķ���
    static Director& getInstance() 
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (getInstanceInternal() == nullptr) {
            getInstanceInternal() = new Director();  // ��ʵ��ʹ���п�����Ҫ�滻Ϊ����ĵ�����Ĵ�������
        }
        return *getInstanceInternal();
    }

    // ��ֹ�������캯���͸�ֵ�����
    Director(const Director&) = delete;
    Director& operator=(const Director&) = delete;

public:
    template <typename T, typename... Args>
    long createObject(Args&&... args)
    {
        long id = m_idManager.getID();
        try
        {
            auto ob = std::shared_ptr<T>(new T(std::forward<Args>(args)...));
            ob->m_id = id;
            m_objects.insert(std::make_pair(id, ob));
            return id;
        }
        catch (...)
        {
            m_idManager.freeID(id);
            return -1;
        }
    }

    std::shared_ptr<ObjectBase> getObject(const long& id)
    {
        if (m_objects.find(id)!= m_objects.end())
        {
            return m_objects[id];
        }
        else
        {
            return nullptr;
        }
    }

private:
    static std::mutex m_mutex;

    IDManager m_idManager;
    std::map<long, std::shared_ptr<ObjectBase>> m_objects;
};
std::mutex Director::m_mutex;
