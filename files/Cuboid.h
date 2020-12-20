#pragma once
#include "Shape.h"

class Cuboid :
    public Shape
{
public:
    Cuboid(const glm::vec3& position, const glm::vec3& size);
    Cuboid(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);
    Cuboid(const glm::vec3& position, const glm::vec3& size, const std::string& texture_path);
    void generateIndices();
    ~Cuboid();
    void init();

    void generateVertices();

};

