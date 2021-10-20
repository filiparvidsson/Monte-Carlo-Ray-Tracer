#pragma once

#include "dependencies.h"

struct Material
{
	dvec3 color;
	double emittance;
	double absorption{ 0.0 };

	Material();
	Material(const dvec3& color);
	Material(const dvec3& color, double emittance);

	virtual std::vector<Ray> brdf(const std::shared_ptr<Ray> &incoming) const = 0;
};

struct Mirror : Material
{
	Mirror();

	std::vector<Ray> brdf(const std::shared_ptr<Ray> &incoming) const override;
};

struct DiffuseLambertian : Material
{
	double reflectance;

	DiffuseLambertian(dvec3 color, double reflectance);

	std::vector<Ray> brdf(const std::shared_ptr<Ray>& incoming) const override;
};

struct Light : Material
{
	Light(dvec3 color, double emittance);

	std::vector<Ray> brdf(const std::shared_ptr<Ray>& incoming) const override;
};