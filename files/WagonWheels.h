#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "Cuboid.h"
class WagonWheels :
    public Composite
{
    
public:
    Cylinder CompartmentWheel1 = Cylinder(glm::vec3(0.45, -0, 0), glm::vec3(0.42, 0.1, 0.42),/* glm::vec3(0, 0, 1)*/"wheel.png");
    Cylinder CompartmentWheel2 = Cylinder(glm::vec3(-0.45, -0, 0), glm::vec3(0.42, 0.1, 0.42),/* glm::vec3(0, 0, 1)*/"wheel.png");
    Cuboid Bar = Cuboid(glm::vec3(0, 0, 0), glm::vec3(1.01, 0.1, 0.1), /*glm::vec3(1, 0, 1)*/"spod.bmp");
    WagonWheels(const glm::vec3& position = { 0,0,0 });
};

