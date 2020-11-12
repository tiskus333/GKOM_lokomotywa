#pragma once
#include "Shape.h"
class Cylinder :
    public Shape
{
    Cylinder();
    ~Cylinder() = default;
    float radius;
    float height;
};

