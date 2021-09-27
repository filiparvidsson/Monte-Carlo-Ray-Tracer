#include "typedefs.h"


Ray::Ray(const dvec3& a, const dvec3& b)
	: start{ a }, end{ b }, direction{ glm::normalize(b - a) } { }

void Ray::setColor(const ColorDbl &newColor)
{
	color = newColor;
}

ColorDbl Ray::getColor()
{
	return this->color;
}

dvec3 Ray::getStart()
{
	return start;
}

dvec3 Ray::getDirection()
{
	return direction;
}

void Ray::setEnd(const double hit) 
{
	end = start + direction * hit;
}

dvec3 Ray::getEnd()
{
	return end;
}

void Ray::localLight(Scene& scene, size_t obj_ind)
{
	Object* obj = scene.getObject(obj_ind);
	for (PointLight& point_light : scene.getPointLights())
	{

		// Check if light is blocked 
		bool occluded = false;
		for (Object* shadow_obj : scene.getObjects())
		{
			// Get length of ray between ray intersection and all point lights
			Ray shadow_ray{ this->end, point_light.position };
			double target_length = glm::length(shadow_ray.end - shadow_ray.start);

			double hitX = shadow_obj->rayIntersection(shadow_ray);
			shadow_ray.setEnd(hitX);

			// Ray intersection is occluded if the intersected ray is shorter than the original ray
			if (hitX > EPSILON && glm::length(shadow_ray.end - shadow_ray.start) < target_length) {
				occluded = true;
				break;
			}
		}
		if (occluded) {
			continue;
		}
		dvec3 hit_to_light = point_light.position - this->end;
		double diffuse = glm::max(glm::dot(glm::normalize(hit_to_light), obj->getNormal(this->getEnd())), 0.0);
		//double fall_off = glm::pow(glm::length(hot_to_light), 2);
		double fall_off = glm::sqrt(glm::length(hit_to_light));
		this->color += diffuse * point_light.color * point_light.intensity / fall_off;
	}
	this->color *= obj->getColor();
}