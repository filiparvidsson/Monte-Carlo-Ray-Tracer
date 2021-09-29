#pragma once

#include "typedefs.h"
#include <array>
#include <vector>


class Object {
public:
	
	virtual double rayIntersection(Ray& ray) = 0;
	virtual dvec3 getNormal(const dvec3& hit) = 0;
	virtual ColorDbl getColor() = 0;
	virtual std::vector<Ray> generateShadowRays(const dvec3& start) = 0;

private:
	
};

class Sphere : public Object {
public:
	Sphere(const dvec3& pos, double rad, const ColorDbl& col)
		: position{ pos }, radius{ rad }, color(col) {};

	double rayIntersection(Ray& ray) override;

	std::vector<Ray> generateShadowRays(const dvec3& start) override;

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
	Triangle() = default;

	double rayIntersection(Ray& ray) override;

	std::vector<Ray> generateShadowRays(const dvec3& start) override;

	dvec3 getNormal(const dvec3& hit) override;

	ColorDbl getColor() override;

private:
	std::array<dvec3, 3> vertices;
	dvec3 normal;
	dvec3 edge1; 
	dvec3 edge2;
	ColorDbl color;
};


class Box : public Triangle {
public:

	Box(const dvec3&, double, double, double, const ColorDbl&);

	std::array<Triangle, 12>& getTriangles();

private:
	std::array<dvec3, 8> corners;
	std::array<Triangle, 12> triangles;
};

