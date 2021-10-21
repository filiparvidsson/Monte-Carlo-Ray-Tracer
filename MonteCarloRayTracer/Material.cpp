#include "dependencies.h"


Material::Material()
	: color{ BLACK }, emittance{ 0.0 }
{
	this->absorption = MIN_ABSORPTION + (MAX_ABSORPTION - MIN_ABSORPTION) * glm::length(color) / glm::length(WHITE);
}

Material::Material(const dvec3& color)
	: color{ color }, emittance{ 0.0 }
{
	this->absorption = MIN_ABSORPTION + (MAX_ABSORPTION - MIN_ABSORPTION) * glm::length(color) / glm::length(WHITE);
}

Material::Material(const dvec3& color, double emittance)
	: color{ color }, emittance{ emittance }
{
	this->absorption = MIN_ABSORPTION + (MAX_ABSORPTION - MIN_ABSORPTION) * glm::length(color) / glm::length(WHITE);
}


Mirror::Mirror()
{
	this->absorption = 0.0;
}

std::vector<Ray> Mirror::brdf(const std::shared_ptr<Ray> &incoming) const
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

Glass::Glass(dvec3 color, double index)
	:Material(color), reflective_index(index) {};

std::vector<Ray> Glass::brdf(const std::shared_ptr<Ray>& incoming) const
{
	vec3 N = incoming->inside_transparant_object ? -incoming->target->getNormal(incoming->end) : incoming->target->getNormal(incoming->end);
	vec3 I = incoming->direction;

	double reflected_importance = 0.0;
	double refracted_importance = 0.0;

	double cos_inc_angle = glm::dot(-I, N);
	double inc_angle = glm::acos(cos_inc_angle);

	double max_angle = glm::asin(AIR_REFLECTIVE_INDEX / this->reflective_index);

	if (incoming->depth < MAX_RAY_DEPTH)
	{
		double R0 = incoming->inside_transparant_object ? glm::pow(((this->reflective_index - AIR_REFLECTIVE_INDEX) / (AIR_REFLECTIVE_INDEX + this->reflective_index)), 2.0)
														: glm::pow(((AIR_REFLECTIVE_INDEX - this->reflective_index) / (AIR_REFLECTIVE_INDEX + this->reflective_index)), 2.0);
		if (incoming->inside_transparant_object && inc_angle > max_angle)
		{
			reflected_importance = incoming->importance;
		}
		else
		{
			// Schlicks equation
			reflected_importance = (R0 + (1.0 - R0) * glm::pow((1.0 - cos_inc_angle), 5.0)) * incoming->importance;
			refracted_importance = (1.0 - reflected_importance) * incoming->importance;
		}
	}
	
	/*if (incoming->inside_transparant_object) {
		std::cout << "inc: " << incoming->importance << "\n";
		std::cout << "r: " << reflected_importance << "\n";
		std::cout << "t : " << refracted_importance << "\n";
		std::cout << "depth: " << incoming->depth << "\n\n";
	}*/


	Ray reflected_ray{ incoming->end + N * RAY_OFFSET_AMOUNT,	// Start with offset
				glm::normalize(glm::reflect(incoming->end, N)),	// Perfect reflection
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
	//result.push_back(reflected_ray);
	result.push_back(refracted_ray);

	return result;
}

DiffuseLambertian::DiffuseLambertian(dvec3 color, double reflectance)
	: Material(color), reflectance{reflectance}{};

std::vector<Ray> DiffuseLambertian::brdf(const std::shared_ptr<Ray> &incoming) const
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
		if (static_cast<double>(rand()) / RAND_MAX < this->absorption)
		{
			reflected_importance = incoming->importance * this->reflectance / (this->absorption * N_DIFFUSE_BOUNCES);
		}

		Ray reflected_ray{ incoming->end + incoming->target->getNormal(incoming->end) * RAY_OFFSET_AMOUNT, world_dir, reflected_importance };

		reflected_ray.depth = incoming->depth + 1;
		
		reflected.push_back(reflected_ray);
	}

	return reflected;
}

Light::Light(dvec3 color, double emittance)
	: Material(color, emittance) {};

std::vector<Ray> Light::brdf(const std::shared_ptr<Ray>& incoming) const
{
	double reflected_importance = 0.0;

	Ray stopped{ incoming->end, glm::normalize(glm::reflect(incoming->end, incoming->target->getNormal(incoming->end))), reflected_importance };

	std::vector<Ray> result;

	result.push_back(stopped);

	return result;
}







