
#ifndef RAY_TNCG15_H //So we wont declare things more than once
#define RAY_TNCG15_H

#include <glm/glm.hpp>
#include "typedefs.h"

//Based on www.youtube.com/watch?v=AHe8PUr7Jqw

class Ray {
public:
	Ray() : Ray(vec3(0.0), vec3(0.0)) {};
	Ray(const vec3&, const vec3&);

	void setColor(const ColorDbl &newColor);

	vec3 getStart();
	vec3 getDirection();

private:
	ColorDbl color = ColorDbl(0.0);
	vec3 start, direction;

};

#endif
