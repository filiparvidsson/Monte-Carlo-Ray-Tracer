#include "typedefs.h"


void Scene::addObject(Object* obj) //Could just make a function addObject
{
    objects.push_back(obj);
}

void Scene::addBox(Box* box)
{
    for (int i = 0; i < box->getTriangles().size(); ++i) {
        addObject(&box->getTriangles()[i]);
    }
}

void Scene::addAreaLight(Object* light)
{
    area_lights.push_back(light);
}

void Scene::addPointLight(PointLight& light)
{
    point_lights.push_back(light);
}

std::vector<Object*>& Scene::getObjects()
{
    return objects;
}

std::vector<Object*>& Scene::getAreaLights()
{
    return area_lights;
}

std::vector<PointLight>& Scene::getPointLights()
{
    return point_lights;
}

Object* Scene::getObject(size_t ind)
{
    return this->objects[ind];
}
