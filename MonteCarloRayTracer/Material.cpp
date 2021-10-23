#include "dependencies.h"


Material::Material(const dvec3& color)
	: color{ color }, emittance{ 0.0 } {};

Material::Material(const dvec3& color, double emittance)
	: color{ color }, emittance{ emittance } {};

Mirror::Mirror()
	: Material(BLACK) {};

DiffuseLambertian::DiffuseLambertian(const dvec3& color, double reflectance)
	: Material(color), reflectance{ reflectance }
{
	this->absorption = MAX_DIFFUSE_ABSORPTION - (MAX_DIFFUSE_ABSORPTION - MIN_DIFFUSE_ABSORPTION) * glm::length(color) / glm::length(WHITE);
};

Light::Light(const dvec3& color, double emittance)
	: Material(color, emittance) {};

Glass::Glass(const dvec3& color, float index)
	:Material(color), reflective_index(index) {};


// The Bidirectional Reflectance Distribution Function of each material determines how incoming rays interact with the material in therms of direction and energy (importance) distribution.

// Perfect reflection, total conservation of importance
std::vector<Ray> Mirror::BRDF(const std::shared_ptr<Ray> &incoming) const
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

	std::vector<Ray> reflected;
	reflected.push_back(reflected_ray);
	
	return reflected;
}

// Both perfectly reflected part and refracted part, total conservation of importance
std::vector<Ray> Glass::BRDF(const std::shared_ptr<Ray>& incoming) const
{
	vec3 N = incoming->inside_transparant_object ? -incoming->target->getNormal(incoming->end) : incoming->target->getNormal(incoming->end);
	vec3 I = incoming->direction;

	double reflected_importance{ 0.0 };
	double refracted_importance{ 0.0 };

	double cos_inc_angle = glm::dot(-I, N);
	double inc_angle = glm::acos(cos_inc_angle);

	double max_angle = glm::asin(AIR_REFLECTIVE_INDEX / this->reflective_index);

	if (incoming->depth < MAX_RAY_DEPTH)
	{
		if (incoming->inside_transparant_object && inc_angle > max_angle)
		{
			reflected_importance = incoming->importance;
		}
		else
		{
			// Schlicks equation
			double R0 = incoming->inside_transparant_object ? glm::pow(((this->reflective_index - AIR_REFLECTIVE_INDEX) / (AIR_REFLECTIVE_INDEX + this->reflective_index)), 2.0)
				: glm::pow(((AIR_REFLECTIVE_INDEX - this->reflective_index) / (AIR_REFLECTIVE_INDEX + this->reflective_index)), 2.0);

			reflected_importance = (R0 + (1.0 - R0) * glm::pow((1.0 - cos_inc_angle), 5.0)) * incoming->importance;
			refracted_importance = (1.0 - reflected_importance) * incoming->importance;
		}
	}

	Ray reflected_ray{ incoming->end + N * RAY_OFFSET_AMOUNT,	// Start with offset
				glm::normalize(glm::reflect(incoming->end, N)),
				reflected_importance };
	
	float reflective_ratio = incoming->inside_transparant_object ? this->reflective_index / AIR_REFLECTIVE_INDEX : AIR_REFLECTIVE_INDEX / this->reflective_index;
	vec3 refracted_direction = reflective_ratio * I + N * (-reflective_ratio * glm::dot(N, I)
									- glm::sqrt(1.0f - glm::pow(reflective_ratio, 2.0f) * (1.0f - glm::pow(glm::dot(N, I), 2.0f))));

	vec3 refracted_start = incoming->end - N * RAY_OFFSET_AMOUNT;

	Ray refracted_ray{ refracted_start, refracted_direction, refracted_importance };

	reflected_ray.inside_transparant_object = incoming->inside_transparant_object;
	refracted_ray.inside_transparant_object = !incoming->inside_transparant_object;

	reflected_ray.depth = incoming->depth + 1;
	refracted_ray.depth = incoming->depth + 1;

	std::vector<Ray> result;
	result.push_back(reflected_ray);
	result.push_back(refracted_ray);

	return result;
}

// Random reflection direction, random ray elimination (Russian Roulette) with probabilities proportianal to material color, loss of importance
std::vector<Ray> DiffuseLambertian::BRDF(const std::shared_ptr<Ray> &incoming) const
{
	vec3 Z = incoming->target->getNormal(incoming->end);
	vec3 X = glm::normalize(incoming->direction - glm::dot(incoming->direction, Z) * Z);
	vec3 Y = normalize(cross(-X, Z));

	// Local coordinates
	glm::mat4 M{X.x, X.y, X.z, 0.0f,
				Y.x, Y.y, Y.z, 0.0f,
				Z.x, Z.y, Z.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };

	std::vector<Ray> reflected;
	
	for (int i = 0; i < N_DIFFUSE_BOUNCES; ++i)
	{
		float phi = (static_cast<float>(rand()) / RAND_MAX) * 2 * static_cast<float>(M_PI);
		float theta = (static_cast<float>(rand()) / RAND_MAX) * static_cast<float>(M_PI_2);

		// Cartesian coordinates
		float x = cos(phi) * sin(theta);
		float y = sin(phi) * sin(theta);
		float z = cos(theta);
		vec3 local_dir = vec3(x, y, z);

		// Transform direction to world coordinates
		vec3 world_dir = glm::inverse(glm::transpose(M)) * glm::vec4(local_dir, 1.0); 

		double reflected_importance = 0.0;

		// Russian Roulette
		if (static_cast<double>(rand()) / RAND_MAX < 1.0 / this->absorption)
		{
			reflected_importance = incoming->importance * this->reflectance / (this->absorption * static_cast<double>(N_DIFFUSE_BOUNCES));
		}

		Ray reflected_ray{ incoming->end + incoming->target->getNormal(incoming->end) * RAY_OFFSET_AMOUNT, world_dir, reflected_importance };

		reflected_ray.depth = incoming->depth + 1;
		
		reflected.push_back(reflected_ray);
	}
	return reflected;
}

// Always stops at light sources
std::vector<Ray> Light::BRDF(const std::shared_ptr<Ray>& incoming) const
{
	double stopped_importance = 0.0;
	
	Ray stopped{ incoming->end, glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))), stopped_importance };

	stopped.depth = incoming->depth + 1;

	std::vector<Ray> result;

	result.push_back(stopped);

	return result;
}
