#pragma once
#include <set>

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

class ObjectBase
{
public:
    friend class Director;
    virtual ~ObjectBase() {}
protected:
    ObjectBase() {};

    long m_id;
private:
};

class Object : public ObjectBase
{
public:
    friend class Director;
protected:
    Object() {};
    
private:
    double cc;
};

class Error : public ObjectBase
{
public:
    friend class Director;
protected:
    Error() 
    {
        std::exception e;
        throw e; 
    };
private:
    double dd;
};