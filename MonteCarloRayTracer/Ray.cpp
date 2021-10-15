#include "dependencies.h"

Ray::Ray(vec3 start, vec3 end)
	: start{ start }, end{ end }, direction{ glm::normalize(end - start) }, importance{ 1.0 }, target{ nullptr }, color{ BLACK } {};

Ray::Ray(vec3 start, vec3 end, double importance)
	: start{ start }, end{ end }, direction{ glm::normalize(end - start) }, importance{ importance }, target{ nullptr }, color{ BLACK } {};

void Ray::setEnd(const float t)
{
	end = start + direction * t;
}

void Ray::AreaLighting(Scene& scene, size_t obj_ind)
{
	Object* obj = scene.getObject(obj_ind);
	dvec3 finalColor = BLACK;

	//According to Lesson
	for (Object* lightSource : scene.area_lights) {

		dvec3 thisLight = BLACK;


		//for (Object* shadowObject : scene.getObjects()) {
			//ColorDbl rayLight = BLACK;
		vec3 endOffset = this->end + 3e-4f * obj->getNormal(this->end);
		std::vector<Ray> shadowRays = lightSource->generateShadowRays(endOffset);
		for (Ray& shadowRay : shadowRays) {
			bool occluded = false;
			float target_length = glm::length(shadowRay.end - shadowRay.start);
			vec3 targetNormal = obj->getNormal(this->end);
			vec3 lightNormal = lightSource->getNormal(shadowRay.end);
			float beta = glm::dot(-shadowRay.direction, lightNormal);
			float alpha = glm::dot(targetNormal, shadowRay.direction);
			//alpha = glm::max(0.0, alpha);
			double cosTerm = alpha * beta;
			cosTerm = glm::max(cosTerm, 0.0);

			for (Object* shadowObject : scene.area_lights) {
				float hitX = shadowObject->rayIntersection(&shadowRay);
				shadowRay.setEnd(hitX);
				//Becomes false for hitX>Epsilon, since it intersects with itself
				if (hitX > 0.002f && glm::length(shadowRay.end - shadowRay.start) < target_length) {
					occluded = true;
					break;
				}
			}
			// Ray intersection is occluded if the intersected ray is shorter than the original ray
			if (!occluded) {

				double dropoff = glm::pow(glm::length(shadowRay.end - shadowRay.start), 2.0);
				thisLight += cosTerm * lightSource->material->color / dropoff;
				thisLight = thisLight;
				finalColor = finalColor;
			}

		}
		finalColor += thisLight / (double)shadowRays.size();

		//finalColor += rayLight;
	} //sqrt for gamma correction = 2
	this->color = sqrt(finalColor * obj->material->color);
}

