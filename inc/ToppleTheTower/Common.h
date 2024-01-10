#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/norm.hpp>

const static float M_PI = 3.14159265359;
const static float M_epsilon = 1e-6;

struct LineSegment 
{
    glm::vec2 start, end;

    LineSegment(const glm::vec2& _start, const glm::vec2& _end) : start(_start), end(_end) {}
};

struct Arc 
{
    glm::vec2 center;
    float radius;
    float startAngle, endAngle;

    Arc(const glm::vec2& _center, float _radius, float _startAngle, float _endAngle)
        : center(_center), radius(_radius), startAngle(_startAngle), endAngle(_endAngle) {}
};