
#include <glm/glm.hpp>
#include <array>
#include "Triangle.h"

Triangle::Triangle(const glm::vec3 &x, const glm::vec3 &y, const glm::vec3 &z)
{
	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;

	// kalkylera normalen enligt glm.g-truc.net/glm.pdf
	normal = glm::normalize(glm::cross(z - x, y - x));
}

bool Triangle::rayIntersection(Ray& arg)
{
	//Möller-Trumbore



	return 0;
}
