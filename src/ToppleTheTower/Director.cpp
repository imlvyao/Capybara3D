#include "Director.h"
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>
std::mutex Director::m_mutex;

bool isEqual(const double& a, const double& b)
{
    return abs(a - b) < M_epsilon;
}

std::shared_ptr<ObjectBase> Director::getObject(const long& id)
{
    if (m_objects.find(id) != m_objects.end())
    {
        return m_objects[id];
    }
    else
    {
        return nullptr;
    }
}

bool Director::removeObject(const long& id)
{
    if (m_objects.find(id) != m_objects.end())
    {
        m_objects.erase(id);
        m_idManager.freeID(id);
        return true;
    }
    else
    {
        return false;
    }
}

bool Collision::isWillBeCollided(
    const CollisionCircle* c1, const glm::vec2& position1, const glm::vec2& velocity1,
    const CollisionBase* c2, const glm::vec2& position2,
    double& allowMaxDis1)
{
    bool re = false;
    if (c1->m_isEnable && c2->m_isEnable)
    {
        const CollisionCircle* pc = dynamic_cast<const CollisionCircle*>(c2);
        const CollisionBox* pb = dynamic_cast<const CollisionBox*>(c2);

        if (pc)
        {
            // 圆与圆碰撞
            auto dis = glm::distance(position1 + velocity1, position2);
            if (dis >= (c1->m_radius + pc->m_radius))  // 未碰撞
            {
                re = false;
                allowMaxDis1 = velocity1.length();
            }
            else  // 碰撞（不考虑穿过）
            {
                re = true;
                allowMaxDis1 = glm::distance(position1, position2)-(c1->m_radius + pc->m_radius);
            }
        }
        else if (pb)
        {
            // 圆与矩形碰撞
            // 构造矩形包围边界
            glm::vec2 vecHor = glm::normalize(glm::vec2(glm::cos(pb->m_angle), glm::sin(pb->m_angle)));

            glm::vec2 vecVer = glm::normalize(glm::vec2(glm::cos(pb->m_angle+M_PI*0.5), glm::sin(pb->m_angle + M_PI * 0.5)));

            glm::vec2 ptLeftUp = position2 + vecVer * (pb->m_h * 0.5f) + vecHor * (pb->m_w * -0.5f);// 左上
            glm::vec2 ptRightUp = position2 + vecVer * (pb->m_h * 0.5f) + vecHor * (pb->m_w * 0.5f);// 右上
            glm::vec2 ptLeftDown = position2 + vecVer * (pb->m_h * -0.5f) + vecHor * (pb->m_w * -0.5f);// 左下
            glm::vec2 ptRightDown = position2 + vecVer * (pb->m_h * -0.5f) + vecHor * (pb->m_w * 0.5f);// 右下

            LineSegment lineUp(ptLeftUp + vecVer * c1->m_radius, ptRightUp + vecVer * c1->m_radius);
            LineSegment lineDown(ptLeftDown - vecVer * c1->m_radius, ptRightDown - vecVer * c1->m_radius);
            LineSegment lineLeft(ptLeftUp - vecHor * c1->m_radius, ptLeftDown - vecHor * c1->m_radius);
            LineSegment lineRight(ptRightUp + vecHor * c1->m_radius, ptRightDown + vecHor * c1->m_radius);

            Arc arcLeftUp(ptLeftUp, c1->m_radius, pb->m_angle + M_PI * 0.5f, pb->m_angle + M_PI);
            Arc arcRightUp(ptRightUp, c1->m_radius, pb->m_angle, pb->m_angle + M_PI*0.5f);
            Arc arcLeftDown(ptLeftDown, c1->m_radius, pb->m_angle + M_PI, pb->m_angle + M_PI*1.5);
            Arc arcRightDown(ptRightDown, c1->m_radius, pb->m_angle + M_PI * 1.5, pb->m_angle);

            // 构造圆运动轨迹线段
            LineSegment circleMove(position1, position1 + velocity1);

            glm::vec2 intersection(-1,-1);
            if (findLineSegmentsIntersection(circleMove, lineUp , &intersection)||
                findLineSegmentsIntersection(circleMove, lineDown, &intersection) ||
                findLineSegmentsIntersection(circleMove, lineLeft, &intersection) ||
                findLineSegmentsIntersection(circleMove, lineRight, &intersection) ||
                findLineSegment2ArcIntersection(circleMove, arcLeftUp, &intersection) ||
                findLineSegment2ArcIntersection(circleMove, arcRightUp, &intersection) ||
                findLineSegment2ArcIntersection(circleMove, arcLeftDown, &intersection) ||
                findLineSegment2ArcIntersection(circleMove, arcRightDown, &intersection) )
            {
                re = true;
                allowMaxDis1 = glm::distance(position1, intersection);
            }

        }
    }
    else
    {
        re = false;
        allowMaxDis1 = velocity1.length();
    }

    return re;
}

bool Collision::findLineSegmentsIntersection(const LineSegment& line1, const LineSegment& line2, glm::vec2* intersection)
{
    const glm::vec2& A = line1.start;
    const glm::vec2& B = line1.end;
    const glm::vec2& C = line2.start;
    const glm::vec2& D = line2.end;
    // 用叉积判断方向
    auto crossProduct = [](glm::vec2 v1, glm::vec2 v2) {
        return v1.x * v2.y - v1.y * v2.x;
    };

    // 向量AC和AD的方向
    glm::vec2 vecAC = { C.x - A.x, C.y - A.y };
    glm::vec2 vecAD = { D.x - A.x, D.y - A.y };

    // 向量CA和CB的方向
    glm::vec2 vecCA = { A.x - C.x, A.y - C.y };
    glm::vec2 vecCB = { B.x - C.x, B.y - C.y };

    // 判断线段AB是否跨越CD
    bool cross1 = crossProduct(vecAC, vecAD) * crossProduct(vecCA, vecCB) >= 0;

    // 向量BC和BD的方向
    glm::vec2 vecBC = { C.x - B.x, C.y - B.y };
    glm::vec2 vecBD = { D.x - B.x, D.y - B.y };

    // 向量DA和DB的方向
    glm::vec2 vecDA = { A.x - D.x, A.y - D.y };
    glm::vec2 vecDB = { B.x - D.x, B.y - D.y };

    // 判断线段CD是否跨越AB
    bool cross2 = crossProduct(vecBC, vecBD) * crossProduct(vecDA, vecDB) >= 0;

    // 判断是否相交
    if (cross1 && cross2) {
        // 计算交点
        double t = crossProduct(vecCA, vecCB) / crossProduct(vecCA, vecCB - vecDA);
        if (intersection!=nullptr)
        {
            intersection->x = A.x + t * (B.x - A.x);
            intersection->y = A.y + t * (B.y - A.y);
        }

        return true;
    }

    return false;
}

bool Collision::findLineSegment2ArcIntersection(const LineSegment& line, const Arc& arc,
    glm::vec2* intersection1, glm::vec2* intersection2)
{
    bool re = false;
    // 先求直线与圆相交
    glm::vec2 ipt1, ipn1, ipt2, ipn2;
    if (glm::intersectLineSphere(line.start, line.end, arc.center, arc.radius, ipt1, ipn1, ipt2, ipn2))
    {
        std::map<double,glm::vec2> ins;
        // 判断交点1是否在线段和圆弧上

        if (isPointOnLineSegment(ipt1,line) && isPointOnArc(ipt1, arc))
        {
            auto dis1 = glm::distance(ipt1, line.start);
            ins.insert(std::make_pair(dis1,ipt1));
        }      

        // 判断交点2是否在线段和圆弧上
        double dis2 = -1;
        if (isPointOnLineSegment(ipt2, line) && isPointOnArc(ipt2, arc))
        {
            auto dis2 = glm::distance(ipt2, line.start);
            ins.insert(std::make_pair(dis2, ipt2));
        }

        if (ins.size() == 1)
        {
            if (intersection1 != nullptr)
            {
                *intersection1 = ins.begin()->second;
            }
            re = true;
        }
        else if(ins.size() ==2)
        {
            if (intersection1 != nullptr)
            {
                *intersection1 = ins.begin()->second;
            }
            if (intersection2 != nullptr)
            {
                *intersection2 = ins.rbegin()->second;
            }
            re = true;
        }
        else
        {
            re = false;
        }
        

    }
    return re;
}

bool Collision::isPointOnLineSegment(const glm::vec2& pt, const LineSegment& line)
{
    // 计算线段的方向向量
    glm::vec2 lineDirection = line.end - line.start;

    // 计算点到线段起点的向量
    glm::vec2 pointToStart = pt - line.start;

    // 计算点到线段终点的向量
    glm::vec2 pointToEnd = pt - line.end;

    // 使用 glm::dot 计算点到线段起点的向量与线段方向向量的点积
    float dotStart = glm::dot(pointToStart, lineDirection);

    // 使用 glm::dot 计算点到线段终点的向量与线段方向向量的点积
    float dotEnd = glm::dot(pointToEnd, -lineDirection);

    // 如果点到线段起点和终点的点积都小于等于0，则点在线段上
    if (isgreaterequal(dotStart,0.0) && isgreaterequal(dotEnd, 0.0f))
    {
        // 检查点到线段的距离是否小于等于线段长度的平方
        float lineLengthSquared = glm::length2(lineDirection);
        glm::vec3 lineDirection3D(lineDirection, 0.0f);
        glm::vec3 pointToStart3D(pointToStart, 0.0f);

        float pointToLineDistanceSquared = glm::length2(glm::cross(lineDirection3D, pointToStart3D)) / lineLengthSquared;

        // 如果点到线段的距离小于等于线段长度的平方，则点在线段上
        return islessequal(pointToLineDistanceSquared, 1.0f);
    }

    return false;
}

bool Collision::isPointOnArc(const glm::vec2& pt, const Arc& arc)
{
    bool re = false;
    float dis = glm::length(pt - arc.center);
    if (isEqual(dis, arc.radius))
    {
        glm::vec2 vecPt = glm::normalize(pt - arc.center);
        const auto vecStart = glm::normalize(glm::vec2(glm::cos(arc.startAngle), glm::sin(arc.startAngle)));
        const auto vecEnd = glm::normalize(glm::vec2(glm::cos(arc.endAngle), glm::sin(arc.endAngle)));
        const auto ptToStartAngle = glm::orientedAngle(vecStart, vecPt);
        const auto endToStartAngle = glm::orientedAngle(vecStart, vecEnd);
        if (islessequal(ptToStartAngle, endToStartAngle) && isgreaterequal(ptToStartAngle,0))
        {
            re = true;
        }
    }
    return re;
}