

#include <glm/glm.hpp>
#include <array>
#include "typedefs.h"
#include "Triangle.h"


Triangle::Triangle(const vec3& x, const vec3& y, const vec3& z, const ColorDbl& newColor)
{

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;

	// kalkylera normalen enligt glm.g-truc.net/glm.pdf
	normal = glm::normalize(glm::cross(z - x, y - x));

	color = newColor;

}


bool Triangle::rayIntersection(Ray& arg)
{
	//Möller-Trumbore



	return 0;
}
