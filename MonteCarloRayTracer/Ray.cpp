#include "dependencies.h"

Ray::Ray(vec3 start, vec3 end)
	: start{ start }, end{ end }, direction{ glm::normalize(end - start) }, importance{ 1.0 }, target{ nullptr }, radiance{ BLACK }, parent{ nullptr } {};

Ray::Ray(vec3 start, vec3 direction, double importance)
	: start{ start }, end{ vec3{0.0f, 0.0f, 0.0f} }, direction{ direction }, importance{ importance }, target{ nullptr }, radiance{ BLACK } {};


void Ray::setEnd(float t)
{
	this->end = this->start + this->direction * t;
}
