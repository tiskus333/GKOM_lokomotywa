#pragma once
#include "Shape.h"

class Floor :
    public Shape
{
    Floor(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, const std::string& texture_path, bool is_light_source);
public:
    Floor(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color, bool is_light_source = false);
    Floor(const glm::vec3& position, const glm::vec3& size, const std::string& texture_path, bool is_light_source = false);
    Floor(const glm::vec3& position, const glm::vec3& size);
    void generateIndices();
    void generateVertices();

    void adjustPosition(const glm::vec3& train_pos);

};


