
#include "Ray.h"

Ray::Ray(const vec3& a, const vec3& b)
{
	start = a;
	direction = b;
}

void Ray::setColor(const ColorDbl &newColor)
{
	color = newColor;
}

vec3 Ray::getStart()
{
	return start;
}

vec3 Ray::getDirection()
{
	return direction;
}
