#pragma once
#include "Shape.h"

class Cuboid :
    public Shape
{
    Cuboid(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, const std::string& texture_path, bool is_light_source);
public:
    Cuboid(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, bool is_light_source = false);
    Cuboid(const glm::vec3 &position, const glm::vec3 &size, const std::string &texture_path, bool is_light_source = false);
    Cuboid(const glm::vec3& position, const glm::vec3& size);
    void generateIndices();
    void generateVertices();

};

