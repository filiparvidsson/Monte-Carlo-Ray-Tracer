
#include "dependencies.h"

void Scene::addObject(Object* obj) //Could just make a function addObject
{
    objects.push_back(obj);
}

void Scene::addAreaLight(Object* light)
{
    area_lights.push_back(light);
}

Object* Scene::getObject(size_t ind)
{
    return this->objects[ind];
}

void Scene::addBox(Box* box)
{
    for (int i = 0; i < box->triangles.size(); ++i) {
        addObject(&box->triangles[i]);
    }
}


//vec3 Scene::traceRay(Ray& ray) const
//{
//    return
//}