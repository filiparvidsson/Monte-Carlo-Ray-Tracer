
#include "Scene.h"
#include "typedefs.h"


void Scene::addObject(Object* obj) //Could just make a function addObject
{
    objects.push_back(obj);
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

// Adds contributions from all point- and area lights to each pixel
void Scene::phongLight(const Ray& ray)
{
    ColorDbl color{ BLACK };
    
    for(PointLight& point_light : getPointLights())
    {

    }

    for (Object* area_light : getAreaLights())
    {

    }

}
