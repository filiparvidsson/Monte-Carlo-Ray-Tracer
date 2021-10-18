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

	if (incoming->depth < MAX_RAY_DEPTH)
	{
		reflected_importance = incoming->importance;
	}
	
	Ray reflected_ray{ incoming->end + incoming->target->getNormal(incoming->end) * RAY_OFFSET_AMOUNT,	// Start with offset
				glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))),	// Perfect reflection
				reflected_importance };
	
	reflected_ray.depth = incoming->depth + 1;
	
	return reflected_ray;
}

DiffuseLambertian::DiffuseLambertian(dvec3 color, double albedo)
	: Material(color), albedo{ albedo }{};

Ray DiffuseLambertian::brdf(const std::shared_ptr<Ray> &incoming) const
{
	// TODO: Small specular reflection
	// TODO: More reflected rays

	vec3 Z = incoming->target->getNormal(incoming->end);
	vec3 X = glm::normalize(incoming->direction - glm::dot(incoming->direction, Z) * Z);
	vec3 Y = normalize(cross(-X, Z));

	// Local coordinates
	glm::mat4 M{X.x, X.y, X.z, 0.0f,
				Y.x, Y.y, Y.z, 0.0f,
				Z.x, Z.y, Z.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };
	
	double phi = (static_cast<double>(rand()) / RAND_MAX) * 2 * M_PI;	// [0, 2*PI] around the normal
	double theta = (static_cast<double>(rand()) / RAND_MAX) * M_PI_2;	// [0, PI/2] towards the normal

	// Cartesian coordinates
	float x = cos(phi) * sin(theta);
	float y = sin(phi) * sin(theta);
	float z = cos(theta);
	vec3 local_dir = vec3(x, y, z);

	// Transform direction to world coordinates
	vec3 world_dir = glm::inverse(glm::transpose(M)) * glm::vec4(local_dir, 1.0); 
	//vec3 worldDir = glm::inverse(M) * glm::vec4(localDir, 1.0); 

	// Russian Roulette
	double reflected_importance = 0.0;
	if (static_cast<double>(rand()) / RAND_MAX < this->reflectance)
	{
		reflected_importance = incoming->importance * this->reflectance;
	}

	Ray reflected_ray{ incoming->end + incoming->target->getNormal(incoming->end) * RAY_OFFSET_AMOUNT, world_dir, reflected_importance };

	reflected_ray.depth = incoming->depth + 1;

	return reflected_ray;
}
