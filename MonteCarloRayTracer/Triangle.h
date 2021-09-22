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
	Triangle() : Triangle(glm::vec3(), glm::vec3(), glm::vec3(), ColorDbl(1.0, 1.0, 1.0)) {};
	Triangle(const vec3&, const vec3&, const vec3&, const ColorDbl&);

	double rayIntersection(Ray &arg);

	ColorDbl getColor();

private:
	std::array<vec3, 3> vertex;
	Direction normal;
	vec3 edge1() const { return vertex[1] - vertex[0]; }
	vec3 edge2() const { return vertex[2] - vertex[0]; }

	ColorDbl color = ColorDbl(0.0);
};



#endif