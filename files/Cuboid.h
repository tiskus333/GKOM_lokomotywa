#pragma once
#include "Shape.h"

class Cuboid :
    public Shape
{
public:
    Cuboid(const glm::vec3 &position, const glm::vec3 &size, bool is_light_source = false);
    Cuboid(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color, bool is_light_source = false);
    Cuboid(const glm::vec3 &position, const glm::vec3 &size, const std::string &texture_path, bool is_light_source = false);
    void generateIndices();
    ~Cuboid();
    void init();

    void generateVertices();

};

