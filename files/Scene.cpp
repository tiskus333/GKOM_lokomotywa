
#include "Scene.h"

Scene::Scene(/* args */) : ambient_light(0.5)
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