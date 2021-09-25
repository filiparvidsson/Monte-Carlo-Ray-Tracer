#ifndef SCENE_TNCG15_H //So we wont declare things more than once
#define SCENE_TNCG15_H

#include <glm/glm.hpp>
#include <vector>
#include "typedefs.h"
#include "Objects.h"


class Scene {

public:
	
    void addObject( Object* obj);

    std::vector<Object*>& getObjects();
    
private:
   
    std::vector<Object*> objects;
};

#endif