#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class Scene
{
private:
    Scene(/* args */);
    ~Scene();

public:
    float ambient_light;
    static Scene& getScene();

    void operator=(const Scene &) = delete;
};