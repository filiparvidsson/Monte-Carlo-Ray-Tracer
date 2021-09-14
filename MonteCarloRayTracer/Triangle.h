#ifndef TRIANGLE_TNCG15_H //So we wont declare things more than once
#define TRIANGLE_TNCG15_H

#include <glm/glm.hpp>
#include "typedefs.h"
#include "Ray.h"
#include <array>

class Triangle {
public:
	//Constructor
	/*glm::vec3 const& x;
	glm::vec3 const& y;
	glm::vec3 const& z;*/
	Triangle() : Triangle(glm::vec3(), glm::vec3(), glm::vec3()) {};
	Triangle(const vec3&, const vec3&, const vec3&);

	bool rayIntersection(Ray &arg);


private:
	std::array<vec3, 3> vertex;
	Direction normal;
	ColorDbl color = ColorDbl(0.0);
};



#endif