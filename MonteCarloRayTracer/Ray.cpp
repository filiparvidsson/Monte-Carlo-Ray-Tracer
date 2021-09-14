
#include "Ray.h"

Ray::Ray(const vec3& a, const vec3& b)
{
	start = a;
	end = b;
}

void Ray::setColor(const ColorDbl &newColor)
{
	color = newColor;
}
