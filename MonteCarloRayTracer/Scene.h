#pragma once
#include "dependencies.h"
#include <vector>

struct Scene {

public:

    std::vector<Object*> objects;
    std::vector<Object*> area_lights;

    void addObject(Object* obj);
    void addAreaLight(Object* light);
    //void addPointLight(PointLight& light);
    void addBox(Box* box);
    Object* getObject(size_t ind);
    //vec3 traceRay(Ray& ray) const;

};
