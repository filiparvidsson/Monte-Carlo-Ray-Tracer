#pragma once

#include "dependencies.h"

struct Material
{
	dvec3 color;
	double emittance;

	Material(const dvec3& color);
	Material(const dvec3& color, double emittance);

	virtual std::vector<Ray> BRDF(const std::shared_ptr<Ray> &incoming) const = 0;
};

struct Mirror : Material
{
	Mirror();

	std::vector<Ray> BRDF(const std::shared_ptr<Ray> &incoming) const override;
};

struct DiffuseLambertian : Material
{
	double absorption;
	double reflectance;

	DiffuseLambertian(const dvec3& color, double reflectance);

	std::vector<Ray> BRDF(const std::shared_ptr<Ray>& incoming) const override;
};

struct Light : Material
{
	Light(const dvec3& color, double emittance);

	std::vector<Ray> BRDF(const std::shared_ptr<Ray>& incoming) const override;
};

struct Glass : Material
{
	float reflective_index;

	Glass(const dvec3& color, float index);

	std::vector<Ray> BRDF(const std::shared_ptr<Ray>& incoming) const override;
};