#pragma once

enum class CollisionType
{
    CollisionBase,
    CollisionBox,
    CollisionCircle,
};
class CollisionBase
{
public:
    virtual ~CollisionBase() {}
    CollisionBase()
    {
        m_isEnable = true;
    }
    bool m_isEnable;
};

class CollisionBox : public CollisionBase
{
public:
    CollisionBox(const float& angle, const float& w, const float& h):m_angle(angle),m_w(w),m_h(h){}
    CollisionBox();
public:
    float m_angle;
    float m_w;
    float m_h;
};

class CollisionCircle : public CollisionBase
{
public:
    CollisionCircle(const float& r) :m_radius(r){}
    CollisionCircle(){}
public:
    float m_radius;
};