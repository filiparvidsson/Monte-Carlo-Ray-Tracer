#pragma once

#include "typedefs.h"
#include <array>


class Object {
public:
	
	virtual double rayIntersection(Ray& ray) = 0;
	virtual dvec3 getNormal(const dvec3& hit) = 0;
	virtual ColorDbl getColor() = 0;

private:
	
};

class Sphere : public Object {
public:
	Sphere(const dvec3& pos, double rad, const ColorDbl& col)
		: position{ pos }, radius{ rad }, color(col) {};

	double rayIntersection(Ray& ray) override;

	dvec3 getNormal(const dvec3& hit) override;

	ColorDbl getColor() override;

private:
	dvec3 position;
	double radius;
	ColorDbl color;
};

class Triangle : public Object {
public:
	
	Triangle(const dvec3&, const dvec3&, const dvec3&, const ColorDbl&);

	double rayIntersection(Ray& ray) override;

	dvec3 getNormal(const dvec3& hit) override;

	ColorDbl getColor() override;

private:
	std::array<dvec3, 3> vertices;
	dvec3 normal;
	dvec3 edge1; 
	dvec3 edge2;
	ColorDbl color;
};

