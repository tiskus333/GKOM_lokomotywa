#pragma once
#include "Shape.h"
class Cylinder :
    public Shape
{
    Cylinder();
    ~Cylinder() = default;
    float radius_;
    float height_;
};

