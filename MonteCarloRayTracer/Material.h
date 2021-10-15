#pragma once

#include "dependencies.h"

struct Material
{
	dvec3 color;
	double emittance;
	double absorption;

	Material();
	Material(const dvec3& color);

	virtual Ray handleRayHit(const Ray& incoming) = 0;
};

struct Mirror : Material
{
	Mirror();

	Ray handleRayHit(const Ray& incoming) override;
};

struct DiffuseLambertian : Material
{
	double albedo;

	DiffuseLambertian(dvec3 color, double albedo);

	Ray handleRayHit(const Ray& incoming) override;
};