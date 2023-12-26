#pragma once
#include <vector>
#include "glm/glm.hpp"
class ActorBase
{
public:

	ActorBase(const double& x, const double& y, const double& ar, const double& cr):
	m_x(x),m_y(y), m_attackRadius(ar), m_collisionRadius(cr)
	{}
	void setXY(const double& x, const double& y)
	{
		m_x = x;
		m_y = y;
	}
	glm::vec2 getXY() 
	{
		return glm::vec2(m_x, m_y);
	}
	void setAttackRadius(const double& r)
	{
		m_attackRadius = r;
	}
	double getAttackRadius()
	{
		return m_attackRadius;
	}
	void setCollisionRadius(const double& r)
	{
		m_collisionRadius = r;
	}
	double getCollisionRadius()
	{
		return m_collisionRadius;
	}
private:
	double m_x;
	double m_y;
	double m_attackRadius;
	double m_collisionRadius;
};

class Footman :public ActorBase
{
public:
	Footman(const double& x, const double& y, const double& ar, const double& cr) :ActorBase(x, y, ar, cr)
	{}
};

class Tower :public ActorBase
{
public:
	Tower(const double& x, const double& y, const double& ar, const double& cr) :ActorBase(x,y,ar,cr)
	{}

};

struct Canvas
{
	Canvas() {}
	Canvas(const double& x, const double& y, const double& w, const double& h) :m_x(x), m_y(y), m_w(w), m_h(h) {}
	double m_x;
	double m_y;
	double m_w;
	double m_h;
};

class Enemy
{
public:
	std::vector<Tower>& getTower() { return m_tower; }
	std::vector<Footman>& getFootman() { return m_footman; }
private:
	std::vector<Tower> m_tower;
	std::vector<Footman> m_footman;
};

class Self
{
public:
	std::vector<Tower>& getTower() { return m_tower; }
	std::vector<Footman>& getFootman() { return m_footman; }
private:
	std::vector<Tower> m_tower;
	std::vector<Footman> m_footman;
};

struct TransData
{
	Canvas m_canvas;
	Enemy m_enemy;
	Self m_self;
};