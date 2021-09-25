#pragma once

#include "typedefs.h"
#include "Ray.h"
#include <array>

class Object {
public:
	
	virtual double rayIntersection(Ray& ray) = 0;
	
	virtual ColorDbl getColor() = 0;

private:
	
};

class Sphere : public Object {
public:
	Sphere(const vec3& pos, double rad, const ColorDbl& col)
		: position{ pos }, radius{ rad }, color(col) {};

	double rayIntersection(Ray& ray) override; //Use override to connect to virtual function

	ColorDbl getColor() override;

private:
	vec3 position;
	double radius;
	ColorDbl color;
};

class Triangle : public Object {
public:
	
	Triangle(const vec3&, const vec3&, const vec3&, const ColorDbl&);

	double rayIntersection(Ray& arg) override;

	ColorDbl getColor() override;

private:
	std::array<vec3, 3> vertices;
	vec3 normal;
	vec3 edge1; 
	vec3 edge2;
	ColorDbl color;
};

