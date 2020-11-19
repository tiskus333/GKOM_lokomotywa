#pragma once
#include "Shape.h"

class Cuboid :
    public Shape
{
public:
    Cuboid(glm::vec3 position, glm::vec3 size);
    Cuboid(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    Cuboid(glm::vec3 position, glm::vec3 size, std::string texture_path);
    void generateIndices();
    ~Cuboid() = default;

    void generateVertices();

};

