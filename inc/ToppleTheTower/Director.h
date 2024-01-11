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
    // 使用局部静态变量确保线程安全的单例实例创建
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

    // 获取单例实例的方法
    static Director& getInstance() 
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (getInstanceInternal() == nullptr) {
            getInstanceInternal() = new Director();  // 在实际使用中可能需要替换为具体的单例类的创建方法
        }
        return *getInstanceInternal();
    }

    // 阻止拷贝构造函数和赋值运算符
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

    double m_timeRate;  //时间速率，默认1.0为现实时间，2.0含义为现实时间1s代表游戏时间2s
    double m_physicalFrame;  //游戏时间下物理行为更新的帧率
};

namespace Collision
{
    bool isPointOnLineSegment(const glm::vec2& pt, const LineSegment& line);

    bool isPointOnArc(const glm::vec2& pt, const Arc& arc);

    bool findLineSegmentsIntersection(const LineSegment& line1, const LineSegment& line2, glm::vec2* intersection = nullptr);
    // 判断圆弧和线段是否相交，并返回交点

    bool findLineSegment2ArcIntersection(const LineSegment& line, const Arc& arc,
        glm::vec2* intersection1 = nullptr, glm::vec2* intersection2 = nullptr);

    bool isWillBeCollided(
        const CollisionCircle* c1, const glm::vec2& position1, const glm::vec2& velocity1,
        const CollisionBase* c2, const glm::vec2& position2,
        double& allowMaxDis1);
}