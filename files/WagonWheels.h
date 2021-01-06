#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "Cuboid.h"
class WagonWheels :
    public Composite
{
    Cylinder CompartmentWheel1(glm::vec3(0.45, -0, 0), glm::vec3(0.42, 0.1, 0.42), glm::vec3(0, 0, 1));
    Cylinder CompartmentWheel2(glm::vec3(-0.45, -0, 0), glm::vec3(0.42, 0.1, 0.42), glm::vec3(0, 0, 1));
    Cuboid Bar(glm::vec3(0, 0, 0), glm::vec3(1.1, 0.1, 0.1), glm::vec3(1, 0, 1));
public:
    WagonWheels();
};

