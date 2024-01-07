#pragma once

class CollisionBase
{

};

class CollisionBox : public CollisionBase
{
private:
    double m_angle;
    double m_w;
    double m_h;
};

class CollisionCircle : public CollisionBase
{
private:
    double m_radius;
};