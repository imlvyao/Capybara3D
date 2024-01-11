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
            // Բ��Բ��ײ
            auto dis = glm::distance(position1 + velocity1, position2);
            if (dis >= (c1->m_radius + pc->m_radius))  // δ��ײ
            {
                re = false;
                allowMaxDis1 = velocity1.length();
            }
            else  // ��ײ�������Ǵ�����
            {
                re = true;
                allowMaxDis1 = glm::distance(position1, position2)-(c1->m_radius + pc->m_radius);
            }
        }
        else if (pb)
        {
            // Բ�������ײ
            // ������ΰ�Χ�߽�
            glm::vec2 vecHor = glm::normalize(glm::vec2(glm::cos(pb->m_angle), glm::sin(pb->m_angle)));

            glm::vec2 vecVer = glm::normalize(glm::vec2(glm::cos(pb->m_angle+M_PI*0.5), glm::sin(pb->m_angle + M_PI * 0.5)));

            glm::vec2 ptLeftUp = position2 + vecVer * (pb->m_h * 0.5f) + vecHor * (pb->m_w * -0.5f);// ����
            glm::vec2 ptRightUp = position2 + vecVer * (pb->m_h * 0.5f) + vecHor * (pb->m_w * 0.5f);// ����
            glm::vec2 ptLeftDown = position2 + vecVer * (pb->m_h * -0.5f) + vecHor * (pb->m_w * -0.5f);// ����
            glm::vec2 ptRightDown = position2 + vecVer * (pb->m_h * -0.5f) + vecHor * (pb->m_w * 0.5f);// ����

            LineSegment lineUp(ptLeftUp + vecVer * c1->m_radius, ptRightUp + vecVer * c1->m_radius);
            LineSegment lineDown(ptLeftDown - vecVer * c1->m_radius, ptRightDown - vecVer * c1->m_radius);
            LineSegment lineLeft(ptLeftUp - vecHor * c1->m_radius, ptLeftDown - vecHor * c1->m_radius);
            LineSegment lineRight(ptRightUp + vecHor * c1->m_radius, ptRightDown + vecHor * c1->m_radius);

            Arc arcLeftUp(ptLeftUp, c1->m_radius, pb->m_angle + M_PI * 0.5f, pb->m_angle + M_PI);
            Arc arcRightUp(ptRightUp, c1->m_radius, pb->m_angle, pb->m_angle + M_PI*0.5f);
            Arc arcLeftDown(ptLeftDown, c1->m_radius, pb->m_angle + M_PI, pb->m_angle + M_PI*1.5);
            Arc arcRightDown(ptRightDown, c1->m_radius, pb->m_angle + M_PI * 1.5, pb->m_angle);

            // ����Բ�˶��켣�߶�
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
    // �ò���жϷ���
    auto crossProduct = [](glm::vec2 v1, glm::vec2 v2) {
        return v1.x * v2.y - v1.y * v2.x;
    };

    // ����AC��AD�ķ���
    glm::vec2 vecAC = { C.x - A.x, C.y - A.y };
    glm::vec2 vecAD = { D.x - A.x, D.y - A.y };

    // ����CA��CB�ķ���
    glm::vec2 vecCA = { A.x - C.x, A.y - C.y };
    glm::vec2 vecCB = { B.x - C.x, B.y - C.y };

    // �ж��߶�AB�Ƿ��ԽCD
    bool cross1 = crossProduct(vecAC, vecAD) * crossProduct(vecCA, vecCB) >= 0;

    // ����BC��BD�ķ���
    glm::vec2 vecBC = { C.x - B.x, C.y - B.y };
    glm::vec2 vecBD = { D.x - B.x, D.y - B.y };

    // ����DA��DB�ķ���
    glm::vec2 vecDA = { A.x - D.x, A.y - D.y };
    glm::vec2 vecDB = { B.x - D.x, B.y - D.y };

    // �ж��߶�CD�Ƿ��ԽAB
    bool cross2 = crossProduct(vecBC, vecBD) * crossProduct(vecDA, vecDB) >= 0;

    // �ж��Ƿ��ཻ
    if (cross1 && cross2) {
        // ���㽻��
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
    // ����ֱ����Բ�ཻ
    glm::vec2 ipt1, ipn1, ipt2, ipn2;
    if (glm::intersectLineSphere(line.start, line.end, arc.center, arc.radius, ipt1, ipn1, ipt2, ipn2))
    {
        std::map<double,glm::vec2> ins;
        // �жϽ���1�Ƿ����߶κ�Բ����

        if (isPointOnLineSegment(ipt1,line) && isPointOnArc(ipt1, arc))
        {
            auto dis1 = glm::distance(ipt1, line.start);
            ins.insert(std::make_pair(dis1,ipt1));
        }      

        // �жϽ���2�Ƿ����߶κ�Բ����
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
    // �����߶εķ�������
    glm::vec2 lineDirection = line.end - line.start;

    // ����㵽�߶���������
    glm::vec2 pointToStart = pt - line.start;

    // ����㵽�߶��յ������
    glm::vec2 pointToEnd = pt - line.end;

    // ʹ�� glm::dot ����㵽�߶������������߶η��������ĵ��
    float dotStart = glm::dot(pointToStart, lineDirection);

    // ʹ�� glm::dot ����㵽�߶��յ���������߶η��������ĵ��
    float dotEnd = glm::dot(pointToEnd, -lineDirection);

    // ����㵽�߶������յ�ĵ����С�ڵ���0��������߶���
    if (isgreaterequal(dotStart,0.0) && isgreaterequal(dotEnd, 0.0f))
    {
        // ���㵽�߶εľ����Ƿ�С�ڵ����߶γ��ȵ�ƽ��
        float lineLengthSquared = glm::length2(lineDirection);
        glm::vec3 lineDirection3D(lineDirection, 0.0f);
        glm::vec3 pointToStart3D(pointToStart, 0.0f);

        float pointToLineDistanceSquared = glm::length2(glm::cross(lineDirection3D, pointToStart3D)) / lineLengthSquared;

        // ����㵽�߶εľ���С�ڵ����߶γ��ȵ�ƽ����������߶���
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