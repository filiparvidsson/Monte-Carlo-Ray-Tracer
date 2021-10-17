#include "dependencies.h"

void Scene::addObject(Object* obj) //Could just make a function addObject
{
    objects.push_back(obj);
}

void Scene::addAreaLight(Object* light)
{
    area_lights.push_back(light);
}

void Scene::addBox(Box* box)
{
    for (int i = 0; i < box->triangles.size(); ++i) {
        addObject(&box->triangles[i]);
    }
}

// Sets the target variable in the input ray
void Scene::rayTarget(Ray& ray) const
{
	float closest_obj = std::numeric_limits<double>::max();

	for (Object* obj : this->objects) {
		float hitX = obj->rayIntersection(&ray);
		if (hitX > 0.0f && hitX < closest_obj) {
			closest_obj = hitX;
			ray.target = obj;
			ray.setEnd(closest_obj);
		}
	}
}

dvec3 Scene::localLighting(Ray& ray) const
{
	dvec3 finalColor = BLACK;

	//According to Lesson
	for (Object* lightSource : this->area_lights) {

		dvec3 thisLight = BLACK;


		//for (Object* shadowObject : scene.getObjects()) {
			//ColorDbl rayLight = BLACK;
		vec3 endOffset = ray.end + 3e-2f * ray.target->getNormal(ray.end);
		std::vector<Ray> shadowRays = lightSource->generateShadowRays(endOffset);

		for (Ray& shadowRay : shadowRays) {

			bool occluded = false;
			float target_length = glm::length(shadowRay.end - shadowRay.start);

			vec3 targetNormal = ray.target->getNormal(ray.end);
			vec3 lightNormal = lightSource->getNormal(shadowRay.end);

			double beta = glm::dot(-shadowRay.direction, lightNormal);
			double alpha = glm::dot(targetNormal, shadowRay.direction);
			//alpha = glm::max(0.0, alpha);
			double cosTerm = alpha * beta;
			cosTerm = glm::max(cosTerm, 0.0);

			for (Object* shadowObject : this->objects) {
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
		finalColor += thisLight / static_cast<double>(shadowRays.size());

		//finalColor += rayLight;
	} //sqrt for gamma correction = 2
	return sqrt(finalColor * ray.target->material->color);
}

// Creates a tree structure of rays none-recursivly to avoid stack overflow
// We first create all rays and when we reach the end (low importance) we set the rays' color
// This function will become more complex as we add more reflected rays and refractions
void Scene::traceRay(std::shared_ptr<Ray> &root) const
{
	std::shared_ptr<Ray> current = root;

	bool is_leaf = false;

	while(true)
	{
		// Creates reflected ray and sets current to the created ray
		if (!is_leaf)
		{
			this->rayTarget(*current);
			

			// TODO Fix so this check is not needed, maybe with offset?
			if (current->target != nullptr)
			{
				Ray reflected = current->target->material->brdf(current);

				reflected.parent = current;
				current->reflected = std::make_shared<Ray>(reflected);

				// Reached a leaf node
				if (reflected.importance < IMPORTANCE_THRESHOLD) {
					is_leaf = true;
				}
				else
				{
					current = current->reflected;
				}
			}
			else
			{
				break;
			}
		}
		// Set ray color
		else {
			current->color += this->localLighting(*current);
			current->color += current->reflected->color * current->reflected->importance;
			
			// Reached the root
			if (current->parent == nullptr)
			{
				break;
			}

			current = current->parent;
		}
	}
}