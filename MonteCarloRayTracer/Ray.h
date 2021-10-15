#pragma once
#include "dependencies.h"

struct Ray
{
	dvec3 color;
	vec3 start;
	vec3 end;
	vec3 direction;

	double importance;

	Object* target;

	std::shared_ptr<Ray> parent;
	std::shared_ptr<Ray> reflected;
	//std::vector<std::shared_ptr<Ray>> reflected;

	Ray() = default;
	Ray(vec3 start, vec3 end);
	Ray(vec3 start, vec3 direction, double importance);

	void setEnd( const float t);
};