#pragma once
#include "Shape.h"

class Cuboid :
    public Shape
{
private:
    glm::vec3 size_;

public:
    Cuboid(glm::vec3 position, glm::vec3 size);
    Cuboid(glm::vec3 position, glm::vec3 size, glm::vec4 color);
    Cuboid(glm::vec3 position, glm::vec3 size, std::string texture_path);
    ~Cuboid() = default;

    void generateVertices();

};

