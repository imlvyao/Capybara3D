#pragma once
#include <iostream>
#include <mutex>
#include <map>
#include <memory>

#include <Common.h>
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
        m_timeRate = 1.0;
        m_physicalFrame = 30.0;
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

    std::shared_ptr<ObjectBase> getObject(const long& id);

    bool removeObject(const long& id);

private:
    static std::mutex m_mutex;

    IDManager m_idManager;
    std::map<long, std::shared_ptr<ObjectBase>> m_objects;

    double m_timeRate;  //ʱ�����ʣ�Ĭ��1.0Ϊ��ʵʱ�䣬2.0����Ϊ��ʵʱ��1s������Ϸʱ��2s
    double m_physicalFrame;  //��Ϸʱ����������Ϊ���µ�֡��
};

namespace Collision
{
    bool isPointOnLineSegment(const glm::vec2& pt, const LineSegment& line);

    bool isPointOnArc(const glm::vec2& pt, const Arc& arc);

    bool findLineSegmentsIntersection(const LineSegment& line1, const LineSegment& line2, glm::vec2* intersection = nullptr);
    // �ж�Բ�����߶��Ƿ��ཻ�������ؽ���

    bool findLineSegment2ArcIntersection(const LineSegment& line, const Arc& arc,
        glm::vec2* intersection1 = nullptr, glm::vec2* intersection2 = nullptr);

    bool isWillBeCollided(
        const CollisionCircle* c1, const glm::vec2& position1, const glm::vec2& velocity1,
        const CollisionBase* c2, const glm::vec2& position2,
        double& allowMaxDis1);
}