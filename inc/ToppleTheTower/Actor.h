#pragma once
#include <vector>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "glm/glm.hpp"
class ActorBase
{
public:
	ActorBase(){}
	ActorBase(const double& x, const double& y, const double& cr, const double& ar):
	m_x(x),m_y(y), m_collisionRadius(cr), m_attackRadius(ar)
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


	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& m_x;
		ar& m_y;
		ar& m_attackRadius;
		ar& m_collisionRadius;
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
	Footman(const double& x, const double& y, const double& cr, const double& ar) :ActorBase(x, y, cr, ar)
	{}
	Footman() {}
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<ActorBase>(*this);
	}
};

class Tower :public ActorBase
{
public:
	Tower(const double& x, const double& y, const double& cr, const double& ar) :ActorBase(x,y,cr,ar)
	{}
	Tower(){}
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<ActorBase>(*this);
	}
};

struct Canvas
{
	Canvas() {}
	Canvas(const double& x, const double& y, const double& w, const double& h) :m_x(x), m_y(y), m_w(w), m_h(h) {}
	double m_x;
	double m_y;
	double m_w;
	double m_h;

	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& m_x;
		ar& m_y;
		ar& m_w;
		ar& m_h;
	}
};

class Enemy
{
public:
	std::vector<Tower>& getTower() { return m_tower; }
	std::vector<Footman>& getFootman() { return m_footman; }
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& m_tower;
		ar& m_footman;
	}

private:
	std::vector<Tower> m_tower;
	std::vector<Footman> m_footman;
};

class Self
{
public:
	std::vector<Tower>& getTower() { return m_tower; }
	std::vector<Footman>& getFootman() { return m_footman; }
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& m_tower;
		ar& m_footman;
	}
private:
	std::vector<Tower> m_tower;
	std::vector<Footman> m_footman;
};

struct TransData
{
	Canvas m_canvas;
	Enemy m_enemy;
	Self m_self;

	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& m_canvas;
		ar& m_enemy;
		ar& m_self;
	}
};