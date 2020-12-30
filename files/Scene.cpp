
#include "Scene.h"

Scene::Scene(/* args */) : ambient_light(0.2, 0.2, 0.2)
{
}

Scene::~Scene()
{
}

Scene &Scene::getScene()
{
    static Scene instance;
    return instance;
}