#pragma once

#include "typedefs.h"
#include "Ray.h"

class Object {
public:
	
	virtual double rayIntersection(const Ray&) = 0;

private:

	ColorDbl color;
	
};

class Sphere : public Object {
public:
	Sphere(dvec3 pos, double rad)
		: position{ pos }, radius{ rad } {};

	double rayIntersection(const Ray& ray);

private:
	dvec3 position;
	double radius;
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