#pragma once

#include "dependencies.h"
#include <iostream>
#include <array>
#include <vector>

struct Object {

	const Material* material;

	Object(const Material* material)
		: material{ material } {};

	virtual float rayIntersection(Ray* ray) = 0;
	virtual vec3 getNormal(const vec3& hit) = 0;
	virtual std::vector<Ray> generateShadowRays(const vec3& start) = 0;
};

struct Sphere : public Object {

	vec3 position;
	double radius;

	Sphere(const vec3& pos, double rad, const Material* material)
		: Object{ material }, position{ pos }, radius{ rad } {};

	float rayIntersection(Ray* ray) override;
	std::vector<Ray> generateShadowRays(const vec3& start) override;
	vec3 getNormal(const vec3& hit) override;

};

struct Triangle : public Object {
	std::array<vec3, 3> vertices;
	vec3 normal;
	vec3 edge1;
	vec3 edge2;

	Triangle(const vec3&, const vec3&, const vec3&, const Material* material);
	Triangle() = default;

	float rayIntersection(Ray* ray) override;
	std::vector<Ray> generateShadowRays(const vec3&) override;
	vec3 getNormal(const vec3& hit) override;

};

//struct Box : public Triangle {
//
//	std::array<dvec3, 8> corners;
//	std::array<Triangle, 12> triangles;
//
//
//	Box(const vec3& pos, float height, float width1, float width2, Material* material);
//
//};