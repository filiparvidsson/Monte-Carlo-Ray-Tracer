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

		dvec3 hot_to_light = point_light.position - this->end;
		double diffuse = glm::max(glm::dot(glm::normalize(hot_to_light), obj->getNormal( this->getEnd() )), 0.0);
		//double fall_off = glm::pow(glm::length(hot_to_light), 2);
		double fall_off = glm::sqrt(glm::length(hot_to_light));
		this->color += diffuse * point_light.color * point_light.intensity / fall_off;
	}
	this->color *= obj->getColor();
}