#include "dependencies.h"


Triangle::Triangle(const vec3& x, const vec3& y, const vec3& z, const Material* material)
	: Object{material} 
{
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = z;

	normal = glm::normalize(glm::cross(z - x, y - x));
	edge1 = y - x;
	edge2 = z - x;
}

Box::Box(const vec3& pos, float height, float depth, float width, const Material* material)
{
	corners[0] = pos + vec3(depth * 0.5f, width * -0.5f, height * 0.5f);
	corners[1] = pos + vec3(depth * -0.5f, width * -0.5f, height * 0.5f);
	corners[2] = pos + vec3(depth * -0.5f, width * 0.5f, height * 0.5f);
	corners[3] = pos + vec3(depth * 0.5f, width * 0.5f, height * 0.5f);
	corners[4] = pos + vec3(depth * 0.5f, width * -0.5f, height * -0.5f);
	corners[5] = pos + vec3(depth * -0.5f, width * -0.5f, height * -0.5f);
	corners[6] = pos + vec3(depth * -0.5f, width * 0.5f, height * -0.5f);
	corners[7] = pos + vec3(depth * 0.5f, width * 0.5f, height * -0.5f);

	//Top
	triangles[0] = Triangle(corners[0], corners[3], corners[1], material);
	triangles[1] = Triangle(corners[1], corners[3], corners[2], material);
	//Bottom
	triangles[2] = Triangle(corners[4], corners[5], corners[6], material);
	triangles[3] = Triangle(corners[4], corners[6], corners[7], material);
	//Wall 1
	triangles[4] = Triangle(corners[0], corners[7], corners[3], material);
	triangles[5] = Triangle(corners[0], corners[4], corners[7], material);
	//Wall 2
	triangles[6] = Triangle(corners[0], corners[1], corners[4], material);
	triangles[7] = Triangle(corners[1], corners[5], corners[4], material);
	//Wall 3
	triangles[8] = Triangle(corners[1], corners[2], corners[5], material);
	triangles[9] = Triangle(corners[2], corners[6], corners[5], material);
	//Wall 4
	triangles[10] = Triangle(corners[3], corners[6], corners[2], material);
	triangles[11] = Triangle(corners[3], corners[7], corners[6], material);

}

vec3 Triangle::getNormal(const vec3&) const
{
	return glm::normalize(glm::cross(this->edge1, this->edge2));
}

vec3 Sphere::getNormal(const vec3& hit) const
{
	return glm::normalize(hit - this->position);
}

float Triangle::rayIntersection(Ray* ray) const
{
	// Moller-Trumbore
	vec3 T = vec3(ray->start - vertices[0]);
	vec3 D = ray->direction;
	vec3 P = glm::cross(D, edge2);
	vec3 Q = glm::cross(T, edge1);

	vec3 hit = (1 / glm::dot(P, edge1)) * vec3(dot(Q, edge2), dot(P, T), dot(Q, D));

	if (hit.x < 0.0f || hit.y < 0.0f || hit.z < 0.0f || hit.z + hit.y > 1.0f) {
		return -1.0f;
	}
	else {
		return hit.x;
	}
}

float Sphere::rayIntersection(Ray* ray) const
{
	// Follows following theroey viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/

	// A = rayStart, B = rayDirection, C = sphereCenter
	// All dot products for the quadratic formula
	vec3 dot_prods{};

	dot_prods.x = glm::dot(ray->direction, ray->direction);
	dot_prods.y = glm::dot(ray->start - this->position, 2.0f * ray->direction);
	dot_prods.z = glm::dot(ray->start - this->position, ray->start - this->position) - this->radius * this->radius;

	// The dicriminant which check for hits
	float discriminant = dot_prods.y * dot_prods.y / 4.0f - dot_prods.x * dot_prods.z;

	// If determinant < 0: No hit, If ==0, It scraped along the surface
	if (discriminant < EPSILON) {
		return -1.0;
	}

	float numerator_neg = -(dot_prods.y / 2.0f * dot_prods.x) - sqrt(discriminant);
	float numerator_pos = -(dot_prods.y / 2.0f * dot_prods.x) + sqrt(discriminant);

	numerator_neg = glm::max(numerator_neg, 0.0f);
	numerator_pos = glm::max(numerator_pos, 0.0f);

	float numerator_true = glm::min(numerator_neg, numerator_pos);

	// Check if hit was behind camera, we dont want that
	if (numerator_true > EPSILON) 
	{
		return numerator_true;
	}

	return -1.0f;
}

// Generate rays that hits random point on the triangular light source
std::vector<Ray> Triangle::generateShadowRays(const vec3& start) const
{
	std::vector<Ray> shadow_rays;
	for (int i = 0; i < N_SHADOW_RAYS; ++i) {
		float u = static_cast<float>(rand() / RAND_MAX);
		float v = (1.0f - u) * (static_cast<float>(rand())) / RAND_MAX;
		vec3 end = this->vertices[0] * (1.0f - u - v) + this->vertices[1] * u + this->vertices[2] * v;
		shadow_rays.push_back(Ray{ start, end });
	}
	return shadow_rays;
}

// TODO: Implement this function properly to be able to have sperical light sources
std::vector<Ray> Sphere::generateShadowRays(const vec3& start) const
{
	std::vector<Ray> shadow_rays;
	shadow_rays.push_back(Ray{ start, this->position });

	return shadow_rays;
}
