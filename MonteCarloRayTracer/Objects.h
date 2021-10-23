#pragma once

#include "dependencies.h"


struct Object {

	const Material* material;

	Object() = default;
	Object(const Material* material)
		: material{ material } {};

	virtual float rayIntersection(Ray* ray) const = 0;
	virtual vec3 getNormal(const vec3& hit) const = 0;
	virtual std::vector<Ray> generateShadowRays(const vec3& start) const = 0;
};

struct Sphere : public Object {

	vec3 position;
	float radius;

	Sphere(const vec3& pos, float rad, const Material* material)
		: Object{ material }, position{ pos }, radius{ rad } {};

	float rayIntersection(Ray* ray) const override;
	std::vector<Ray> generateShadowRays(const vec3& start) const override;
	vec3 getNormal(const vec3& hit) const override;
};

struct Triangle : public Object {

	std::array<vec3, 3> vertices;

	vec3 normal;
	vec3 edge1;
	vec3 edge2;

	Triangle() = default;
	Triangle(const vec3&, const vec3&, const vec3&, const Material* material);

	float rayIntersection(Ray* ray) const override;
	std::vector<Ray> generateShadowRays(const vec3& start) const override;
	vec3 getNormal(const vec3& hit) const override;
};

struct Box : public Triangle {

	std::array<vec3, 8> corners;
	std::array<Triangle, 12> triangles;

	Box() = default;
	Box(const vec3& pos, float height, float depth, float width, const Material* material);
};
