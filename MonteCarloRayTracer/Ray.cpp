#include "dependencies.h"

Ray::Ray(vec3 start, vec3 end)
	: start{ start }, end{ end }, direction{ glm::normalize(end - start) }, importance{ 1.0 }, radiance{ 0.0 }, target{ nullptr }, color{ BLACK }, parent{ nullptr } {};

Ray::Ray(vec3 start, vec3 direction, double importance)
	: start{ start }, end{ vec3{0.0f, 0.0f, 0.0f} }, direction{ direction }, importance{ importance }, radiance{ 0.0 }, target{ nullptr }, color{ BLACK } {};


void Ray::setEnd(const float t)
{
	end = start + direction * t;
}
