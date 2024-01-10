#pragma once
#include <set>
#include <glm/glm.hpp>

#include "Collision.h"

class Director;
class IDManager
{
public:
    long getID() 
    {
        long re = -1;
        if (!m_freedIDs.empty())
        {
            long id = *m_freedIDs.begin();
            re = id;
            m_freedIDs.erase(id);
            m_usedIDs.insert(id);
        }
        else if (m_usedIDs.empty())
        {
            long id = 0;
            re = id;
            m_usedIDs.insert(id);
        }
        else
        {
            long id = *m_usedIDs.rbegin();
            re = ++id;
            m_usedIDs.insert(id);
        }
        return re;
    };
    bool freeID(const long& id) 
    {
        bool re = false;
        if (m_usedIDs.find(id)!=m_usedIDs.end())
        {
            m_usedIDs.erase(id);
            m_freedIDs.insert(id);
        }
        return re;
    };

    std::set<long> m_usedIDs;
    std::set<long> m_freedIDs;
};

enum class ObjectType
{
    ObjectBase,
    Wall,
    Ball,
};

class ObjectBase
{
public:
    friend class Director;
    virtual ~ObjectBase() {}
    virtual ObjectType getType() { return m_type; }

    glm::vec2 getPositon(){return m_position; }

    void setPosition(const glm::vec2& p)
    {
        m_position = p;
    }

    glm::vec2 getVelocity() { return m_velocity; }

    void setVelocity(const glm::vec2& v)
    {
        m_velocity = v;
    }
protected:
    ObjectBase() 
    {
        m_type = ObjectType::ObjectBase;
    };

    long m_id;
    ObjectType m_type;

    glm::vec2 m_position;
    glm::vec2 m_velocity;  //ÀŸ∂» ∏¡ø
private:
};

class Wall : public ObjectBase
{
public:
    friend class Director;
protected:
    Wall() 
    {
        m_type = ObjectType::Wall;
    };

private:
    CollisionBox m_collisionBox;
};

class Ball : public ObjectBase
{
public:
    friend class Director;
protected:
    Ball()
    {
        m_type = ObjectType::Ball;
    };

private:
    CollisionCircle m_collisionCircle;
};