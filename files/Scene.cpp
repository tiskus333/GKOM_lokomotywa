
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

void Scene::setVec3InShaders(const std::string &name, glm::vec3 &value)
{
    shape_shader.Use();
    shape_shader.setVec3(name,value);
    light_shader.setVec3(name,value);
}


void Scene::setMatrix4fvInShaders(const std::string &name, glm::mat4 &matrix)
{
    shape_shader.setMatrix4fv(name,matrix);
    light_shader.setMatrix4fv(name,matrix);
}