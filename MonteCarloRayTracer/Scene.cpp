#include "dependencies.h"

void Scene::addObject(Object* obj) //Could just make a function addObject
{
    objects.push_back(obj);
}

void Scene::addAreaLight(Object* light)
{
    area_lights.push_back(light);
	//Add lights to the scene to see them
	objects.push_back(light);
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

	if (ray.target == nullptr) return finalColor;

	if (ray.target->material->emittance != 0.0) {
		return ray.target->material->color;
	}

	//According to Lesson
	for (Object* lightSource : this->area_lights) {

		dvec3 thisLight = BLACK;

		vec3 endOffset = ray.end + ray.target->getNormal(ray.end) * RAY_OFFSET_AMOUNT;
		std::vector<Ray> shadowRays = lightSource->generateShadowRays(endOffset);

		for (Ray& shadowRay : shadowRays) {

			bool occluded = false;
			float target_length = glm::length(shadowRay.end - shadowRay.start);

			vec3 targetNormal = ray.target->getNormal(ray.end);
			vec3 lightNormal = lightSource->getNormal(shadowRay.end);

			double beta = glm::dot(-shadowRay.direction, lightNormal);
			double alpha = glm::dot(targetNormal, shadowRay.direction);
			double cosTerm = alpha * beta;
			cosTerm = glm::max(cosTerm, 0.0);

			for (Object* shadowObject : this->objects) {
				
				Ray temp = shadowRay;

				if (shadowObject->material->emittance == 0.0) {
					float hitX = shadowObject->rayIntersection(&shadowRay);
					
					temp.setEnd(hitX);

					if (hitX > EPSILON && glm::length(temp.end - temp.start) < target_length) {
						occluded = true;
						break;
					}
				}
			}
			// Ray intersection is occluded if the intersected ray is shorter than the original ray
			if (!occluded) {
				double dropoff = glm::pow(glm::length(shadowRay.end - shadowRay.start), 2);
				thisLight += lightSource->material->emittance * cosTerm * lightSource->material->color / (dropoff * area_lights.size());
			}
		}
		finalColor += thisLight / static_cast<double>(shadowRays.size());
	} 
	return finalColor * ray.target->material->color;
}

// Creates a tree structure of rays none-recursivly to avoid stack overflow
// We first create all rays and when we reach the end (low importance) we set the rays' color
// Each ray can have any number of children that will all contribute to the result
void Scene::traceRay(std::shared_ptr<Ray> &root) const
{
	std::shared_ptr<Ray> current = root;

	// TODO:
	// FIX THIS SHIT
	while(true)
	{
		// Sets color from local lighting for leaf node
		if (current->importance < IMPORTANCE_THRESHOLD)
		{
			this->rayTarget(*current);

			if (current->target == nullptr)
			{
				break;
			}
			current->is_leaf = true;

			dvec3 local_color = this->localLighting(*current);
			current->radiance = glm::length(local_color);
			current->color = local_color;// * current->radiance;
			current = current->parent;
		}
		// Create child rays if there are none and current isn't a leaf node
		else if (current->children.size() == 0)
		{
			this->rayTarget(*current);

			if (current->target == nullptr)
			{
				break;
			}
			std::vector<Ray> child_rays = current->target->material->brdf(current);

			for (Ray& r : child_rays)
			{
				r.parent = current;
				current->children.push_back(std::make_shared<Ray>(r));
			}
		}
		// Iterate through all child nodes, if all are leaves, evaluate color, delete children, make current a leaf and set current to parent.
		// If a child branch is not yet evaluated, evaluate that branch by setting current to that child.
		else
		{
			bool evaluate = true;
			for (std::shared_ptr<Ray>& child : current->children)
			{
				// Checks if child branch needs evaluation
				if (!child->is_leaf)
				{
					current = child;
					evaluate = false;
					break;
				}
			}

			if (evaluate)
			{
				dvec3 local_color = this->localLighting(*current);
				current->radiance = glm::length(local_color);

				for (std::shared_ptr<Ray>& child : current->children)
				{
					current->radiance += child->radiance * child->importance / current->importance;

				}
				current->color = local_color * current->radiance;
				for (std::shared_ptr<Ray>& child : current->children)
				{
					current->color += child->color * GLOBAL_COLOR_CONTRIBUTION;  
					child.reset();
				}

				// Reached the root
				if (current->parent == nullptr)
				{
					current.reset();	// Current and root points to the same ray, delete the extra node
					break;	// End the function
				}
				current->is_leaf = true;
				current = current->parent;
			}
		}
	}
}