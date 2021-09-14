#ifndef SCENE_TNCG15_H //So we wont declare things more than once
#define SCENE_TNCG15_H

#include <glm/glm.hpp>
#include <vector>
#include "typedefs.h"
#include "Triangle.h"

class Scene {

public:
	Scene();

private:
	std::vector<Triangle> triangles;

};

#endif