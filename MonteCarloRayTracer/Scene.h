#pragma once
#include "dependencies.h"


struct Scene {

public:

    std::vector<Object*> objects;
    std::vector<Object*> area_lights;

    void addObject(Object* obj);
    void addAreaLight(Object* light);
    void addBox(Box* box);

    void rayTarget(Ray& ray) const;
    dvec3 localLighting(const Ray& ray) const;
    void traceRay(std::shared_ptr<Ray> &root) const;
};
