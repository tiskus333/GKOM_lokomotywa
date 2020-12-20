
#include "Scene.h"

Scene::Scene(/* args */) : ambient_light(0.3)
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