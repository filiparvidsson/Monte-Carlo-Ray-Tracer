#pragma once

#include "typedefs.h"
#include "Ray.h"

class Object {
public:
	
	virtual double rayIntersection(const Ray&) = 0;
	virtual ~Object();

private:
	
};

class Sphere : public Object {
public:
	Sphere(ColorDbl col, dvec3 pos, double rad)
		: color(col), position{ pos }, radius{ rad } {};

	double rayIntersection(const Ray& ray);

	ColorDbl getColor();

private:
	dvec3 position;
	double radius;
	ColorDbl color;
};

//class Triangle : Object {
//public:
//
//private:
//
//};



//class Box : Triangle {
//
//};