#include "dependencies.h"

Material::Material()
	: color{ BLACK }, emittance{ 0.0 }, reflectance{ 1.0 }{};

Material::Material(const dvec3& color)
	: color{ color }, emittance{ 0.0 }
{
	reflectance = MIN_REFLECTANCE + (MAX_REFLECTANCE - MIN_REFLECTANCE) * glm::length(color) / glm::length(WHITE);
}

Mirror::Mirror()
{
	this->reflectance = 0.0;
}

Ray Mirror::brdf(const std::shared_ptr<Ray> &incoming) const
{
	double reflected_importance = 0.0;

	if (this->russianRoulette())
	{
		// Perfect reflection with no loss of importance
		reflected_importance = incoming->importance;
	}

	return Ray{ incoming->end, glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))), reflected_importance };
}

DiffuseLambertian::DiffuseLambertian(dvec3 color, double albedo)
	: Material(color), albedo{ albedo }{};

Ray DiffuseLambertian::brdf(const std::shared_ptr<Ray> &incoming) const
{
	// TODO: Small specular reflection
	// TODO: More reflected rays

	double reflected_importance = 0.0;

	// Random angles
	double phi = (static_cast<double>(rand()) / (RAND_MAX + 1.0)) * 2 * M_PI;	// [0, 2*PI] around the normal
	double theta = (static_cast<double>(rand()) / (RAND_MAX + 1.0)) * M_PI_2;	// [0, PI/2] towards the normal

	vec3 normal{ incoming->target->getNormal(incoming->end) };

	// Transform normal to spherical coordinates
	// Normal is normalized so r = 1
	vec3 reflected_spherical{	1.0f,
								atan2(normal.g, normal.r),
								atan2(sqrt(normal.r * normal.r + normal.g * normal.g), normal.b) };

	// Adding radnomized angles to the spherical coordinates
	reflected_spherical.g += phi;
	reflected_spherical.b += theta;

	// Transofrming back to cartesian coordinates
	vec3 reflected_cartesian{	cos(reflected_spherical.g) * sin(reflected_spherical.b),
								sin(reflected_spherical.g) * sin(reflected_spherical.b),
								cos(reflected_spherical.b) };

	if (this->russianRoulette())
	{
		reflected_importance = incoming->importance * this->reflectance;
	}
	
	return Ray{ incoming->end, reflected_cartesian, reflected_importance };
}

bool Material::russianRoulette() const
{
	if (static_cast<double>(rand()) / (RAND_MAX + 1.0) < R_ROULETTE_THRESHOLD)
	{
		return false;
	}
	return true;
}
