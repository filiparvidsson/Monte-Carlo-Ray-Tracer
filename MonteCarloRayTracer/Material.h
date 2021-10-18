#pragma once

#include "dependencies.h"

struct Material
{
	dvec3 color;
	double emittance;
	double reflectance;

	Material();
	Material(const dvec3& color);

	virtual std::vector<Ray> brdf(const std::shared_ptr<Ray> &incoming) const = 0;
};

struct Mirror : Material
{
	Mirror();

	std::vector<Ray> brdf(const std::shared_ptr<Ray> &incoming) const override;
};

struct DiffuseLambertian : Material
{
	double albedo;

	DiffuseLambertian(dvec3 color, double albedo);

	std::vector<Ray> brdf(const std::shared_ptr<Ray> &incoming) const override;
};