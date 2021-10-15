#include "dependencies.h"

Material::Material()
	: color{ BLACK }, emittance{ 0.0 }, absorption{ 1.0 }{};

Material::Material(const dvec3& color)
	: color{ color }, emittance{ 0.0 }
{
	absorption = MIN_ABSORP + (MAX_ABSORP - MIN_ABSORP) * glm::length(color) / glm::length(WHITE);
}

Mirror::Mirror()
{
	this->absorption = 0.0;
}

Ray Mirror::brdf(const std::shared_ptr<Ray> incoming) const
{
	// Perfect reflection with no loss of importance
	Ray reflected{ incoming->end, glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))), incoming->importance };

	return reflected;
}

DiffuseLambertian::DiffuseLambertian(dvec3 color, double albedo)
	: Material(color), albedo{ albedo }{};

Ray DiffuseLambertian::brdf(const std::shared_ptr<Ray> incoming) const
{
	// Temporary ray stop because importance sets to 0.0
	return Ray{ incoming->end, incoming->end, 0.0 };
}