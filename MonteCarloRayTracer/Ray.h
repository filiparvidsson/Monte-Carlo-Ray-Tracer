#pragma once
#include "dependencies.h"

struct Ray
{
	vec3 start;
	vec3 end;
	vec3 direction;
	dvec3 radiance;
	double importance;

	int depth{ 0 };
	bool is_leaf{ false };
	bool inside_transparant_object{ false };

	Object* target;

	std::shared_ptr<Ray> parent;
	std::vector<std::shared_ptr<Ray>> children;

	Ray() = default;
	Ray(vec3 start, vec3 end);
	Ray(vec3 start, vec3 direction, double importance);

	void setEnd(float t);
};