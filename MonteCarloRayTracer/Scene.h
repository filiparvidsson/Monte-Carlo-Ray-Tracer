#ifndef SCENE_TNCG15_H //So we wont declare things more than once
#define SCENE_TNCG15_H

#include <glm/glm.hpp>
#include <vector>
#include "typedefs.h"
#include "Triangle.h"
#include "Objects.h"


class Scene {

public:
	Scene();

    void loadTriangles();
    
    void addSphere(dvec3 pos, double rad);

    std::vector<Triangle>& getTriangles();
    
private:
   
    std::vector<Triangle> triangles;
    std::vector<Object> objects;

};

#endif