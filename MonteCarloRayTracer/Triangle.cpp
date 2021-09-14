

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
	vec3 T = vec3(arg.getStart() - vertex[0]);
	vec3 E1 = vec3(vertex[1] - vertex[0]);
	vec3 E2 = vec3(vertex[2] - vertex[0]);
	vec3 D = vec3(arg.getEnd() - arg.getStart());
	vec3 P = glm::cross(D, E2);
	vec3 Q = glm::cross(T, E1);

	double determinant = glm::dot(P, E1);

	if (abs(determinant) < EPSILON) return false; //They parallel, thus determinant is 0

	double invdeterminant = 1.0 / determinant;

	double u = invdeterminant * glm::dot(Q, E2); //Skalärprodukt
	if (u >= EPSILON) return false;

	double v = invdeterminant * glm::dot(P, T);
	if (v >= EPSILON || u + v <= 1.0) return false;

	double t = invdeterminant * glm::dot(Q, D);
	if (t > EPSILON) //In case an object blocks the camera
		return true;
	else
		return false;

}
