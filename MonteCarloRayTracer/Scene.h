#ifndef SCENE_TNCG15_H //So we wont declare things more than once
#define SCENE_TNCG15_H

#include <glm/glm.hpp>
#include <vector>
#include "typedefs.h"
#include "Objects.h"
#include "Ray.h"
#include "PointLight.h"


class Scene {

public:
	
    void addObject(Object* obj);

    void addAreaLight(Object* light);

    void addPointLight(PointLight& light);

    std::vector<Object*>& getObjects();

    std::vector<Object*>& getAreaLights();

    std::vector<PointLight>& getPointLights();

    void phongLight(const Ray& ray);
    
private:
   
    std::vector<Object*> objects;
    std::vector<Object*> area_lights;
    std::vector<PointLight> point_lights;
};

#endif