#pragma once
#include "Composite.h"
#include "Cuboid.h"
class SmokeParticle :
    public Composite
{
    Cuboid c1 = Cuboid({ 0,0,0 }, { 0.2,0.2,0.2 }, glm::vec3(1, 1, 1));
    Cuboid c2 = Cuboid({ 0,0,0 }, { 0.2,0.2,0.2 }, glm::vec3(1, 1, 1));
public:
    float lifeTime = 0.0f;
    float maxLifeTime = 2.0f;
    SmokeParticle(const glm::vec3& position,float maxLife);
    bool update(float deltaTime);
    void scale(const glm::vec3& scale);
};

