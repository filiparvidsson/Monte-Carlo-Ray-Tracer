#pragma once
#include "dependencies.h"

struct Ray
{
	dvec3 color;
	vec3 start;
	vec3 end;
	vec3 direction;

	double importance;

	std::shared_ptr<Object> target;

	Ray(vec3 start, vec3 end);
	Ray(vec3 start, vec3 direction, double importance);

	void setEnd( const float t);
	//AreaLight
	void localLight(Scene& scene, size_t obj_ind);

};