
#include "Scene.h"

Scene::Scene(/* args */) : ambient_light(0.2, 0.2, 0.2)
{
    shape_shader = ShaderProgram("CubeShader.vert", "CubeShader.frag");
    light_shader = ShaderProgram("LightShader.vert", "LightShader.frag");
}

Scene::~Scene()
{
}

Scene &Scene::getScene()
{
    static Scene instance;
    return instance;
}