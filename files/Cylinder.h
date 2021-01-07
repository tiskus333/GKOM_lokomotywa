#pragma once
#include "Shape.h"
class Cylinder :
    public Shape
{
public:
    Cylinder(const glm::vec3& position, const glm::vec3& size, bool is_light_source = false);
    Cylinder(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, bool is_light_source = false);
    Cylinder(const glm::vec3& position, const glm::vec3& size, const std::string& texture_path, bool is_light_source = false);
    static const uint32_t SEGMENTS = 32;
    float radius_;
    float height_;
    void generateIndices();
    void generateVertices();
    void init();
};

