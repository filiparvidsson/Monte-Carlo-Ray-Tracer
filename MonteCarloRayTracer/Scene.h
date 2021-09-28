#ifndef SCENE_TNCG15_H //So we wont declare things more than once
#define SCENE_TNCG15_H

#include "typedefs.h"
#include <vector>


class Scene {

public:
	
    void addObject(Object* obj);

    void addBox(Box* box);

    void addAreaLight(Object* light);

    void addPointLight(PointLight& light);

    std::vector<Object*>& getObjects();

    Object* getObject(size_t ind);

    std::vector<Object*>& getAreaLights();

    std::vector<PointLight>& getPointLights();
    
private:
   
    std::vector<Object*> objects;
    std::vector<Object*> area_lights;
    std::vector<PointLight> point_lights;
};

#endif