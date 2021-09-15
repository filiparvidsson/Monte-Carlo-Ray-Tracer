

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


bool Triangle::rayIntersection(Ray& arg)
{
	//Möller-Trumbore
	vec3 T = vec3(arg.getStart() - vertex[0]);
	vec3 E1 = this->edge1();
	vec3 E2 = this->edge2();
	vec3 D = glm::normalize(arg.getDirection());
	vec3 P = glm::cross(D, E2);
	vec3 Q = glm::cross(T, E1);

	double determinant = glm::dot(P, E1);
	

	if (abs(determinant) < EPSILON) {
		//std::cout << "ray was not intersected" << std::endl;
		return false; //They parallel, thus determinant is 0
		
	}
	double invdeterminant = 1.0 / determinant;
	//std::cout << invdeterminant << std::endl;

	double u = invdeterminant * glm::dot(P, T); //Skalärprodukt
	if (u >= EPSILON || u > 1.0f) {
		//std::cout << "ray was not intersected" << std::endl;
		return false; 

	}

	double v = invdeterminant * glm::dot(Q, D);
	if (v >= EPSILON && u + v <= 1.0f) {
		//std::cout << "u = " << u << " and v = " << v << std::endl;
		return false; 

	}
	else {
		//std::cout << u+v << std::endl;
	}

	double t = invdeterminant * glm::dot(Q, E2);
	if (t > EPSILON) //In case an object blocks the camera

		return true;
	else
		//std::cout << "ray was not intersected, t = " << t << std::endl;
		return false;

}

ColorDbl Triangle::getColor()
{
	return color;
}
