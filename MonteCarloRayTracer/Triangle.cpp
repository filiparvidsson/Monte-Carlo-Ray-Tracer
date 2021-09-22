

#include <glm/glm.hpp>
#include <array>
#include "typedefs.h"
#include "Triangle.h"
#include <iostream>


Triangle::Triangle(const vec3& x, const vec3& y, const vec3& z, const ColorDbl& newColor)
{

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;

	// kalkylera normalen enligt glm.g-truc.net/glm.pdf
	normal = glm::normalize(glm::cross(z - x, y - x));

	color = newColor;

}


double Triangle::rayIntersection(Ray& arg)
{
	//Möller-Trumbore
	vec3 T = vec3(arg.getStart() - vertex[0]);
	vec3 E1 = this->edge1();
	vec3 E2 = this->edge2();
	vec3 D = arg.getDirection();
	vec3 P = glm::cross(D, E2);
	vec3 Q = glm::cross(T, E1);

	double determinant = glm::dot(P, E1);
	
	

	if (abs(determinant) < EPSILON) {
		//std::cout << "ray was not intersected" << std::endl;
		return -1.0; //They parallel, thus determinant is 0
		
	}
	double invdeterminant = 1.0 / determinant;
	//std::cout << invdeterminant << std::endl;

	vec3 hit = vec3(invdeterminant * glm::dot(Q, E2) * glm::dot(P, T), invdeterminant * glm::dot(P, T), invdeterminant * glm::dot(Q, D));

	if (hit.x < EPSILON || hit.y < EPSILON || hit.y > 1.0f || hit.z < EPSILON || hit.z + hit.y > 1.0f) {
		return -1.0;
	}
	else {
		return hit.x;
	}

	

}

ColorDbl Triangle::getColor()
{
	return color;
}
