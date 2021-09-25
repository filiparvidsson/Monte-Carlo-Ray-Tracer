
#include "Scene.h"
#include "typedefs.h"


void Scene::addObject(Object* obj) //Could just make a function addObject
{
    objects.push_back(obj);
}

std::vector<Object*>& Scene::getObjects()
{
    return objects;
}
