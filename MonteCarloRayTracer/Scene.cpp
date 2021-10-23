#include "dependencies.h"


void Scene::addObject(Object* obj)
{
    objects.push_back(obj);
}

void Scene::addAreaLight(Object* light)
{
    area_lights.push_back(light);
	objects.push_back(light);
}

void Scene::addBox(Box* box)
{
    for (size_t i = 0; i < box->triangles.size(); ++i) {
        addObject(&box->triangles[i]);
    }
}

// Sets the target and end variables of the input ray
void Scene::rayTarget(Ray& ray) const
{
	float closest_obj = std::numeric_limits<float>::max();

	for (Object* obj : this->objects) {
		float hitX = obj->rayIntersection(&ray);
		if (hitX > 0.0f && hitX < closest_obj) {
			closest_obj = hitX;
			ray.target = obj;
			ray.setEnd(closest_obj);
		}
	}
}

// Takes a ray with a set target object as input. Returns the radiance in the scene in the end point of that ray.
dvec3 Scene::localLighting(const Ray& incoming_ray) const
{
	dvec3 final_radiance = BLACK;

	if (incoming_ray.target == nullptr) return final_radiance; // TODO: Fix the bug that causes this exception

	if (incoming_ray.target->material->emittance != 0.0) {
		return incoming_ray.target->material->color;
	}

	// Shoots shadow ray(s) towards a random point(s) on every light source in the scene.
	// A light source contributes radiance if it isn't occluded by other objects in the scene.
	for (Object* light_source : this->area_lights) {

		dvec3 light_radiance = BLACK;

		// Offset the end of the incoming ray so that the shadow rays won't be intercepted by the object they are starting from
		vec3 end_offset = incoming_ray.end + incoming_ray.target->getNormal(incoming_ray.end) * RAY_OFFSET_AMOUNT;
		std::vector<Ray> shadow_rays = light_source->generateShadowRays(end_offset);

		for (Ray& sr : shadow_rays) {

			bool occluded = false;
			float target_length = glm::length(sr.end - sr.start);

			// Check if every object in the scene occludes the light source 
			for (Object* shadow_object : this->objects) {
				
				Ray temp = sr;
				// Ignore light sources and transparent objects
				if (dynamic_cast<const Light*>(shadow_object->material) == nullptr && dynamic_cast<const Glass*>(shadow_object->material) == nullptr) {
					float hit_x = shadow_object->rayIntersection(&sr);
					
					temp.setEnd(hit_x);

					if (hit_x > EPSILON && glm::length(temp.end - temp.start) < target_length) {
						occluded = true;
						break;
					}
				}
			}
			
			if (!occluded) {
				// The light contribution depends on the angle of the surface towards the light source and the distance from the light
				double beta = glm::dot(-sr.direction, light_source->getNormal(sr.end));
				double alpha = glm::dot(incoming_ray.target->getNormal(incoming_ray.end), sr.direction);
				double cos_term = alpha * beta;
				cos_term = glm::max(cos_term, 0.0);

				double dropoff = glm::pow(glm::length(sr.end - sr.start), DROPOFF_POWER);

				light_radiance += light_source->material->emittance * cos_term * light_source->material->color / (dropoff * area_lights.size());
			}
		}
		final_radiance += light_radiance / static_cast<double>(shadow_rays.size());
	} 
	return final_radiance * incoming_ray.target->material->color;
}

// Creates a tree structure of rays none-recursivly to avoid stack overflow.
// We first create all rays and when we reach the end (low importance) we set the rays' radiance.
// Each ray can have any number of children that will all contribute to the result.
void Scene::traceRay(std::shared_ptr<Ray> &root) const
{
	std::shared_ptr<Ray> current = root;

	while(true)
	{
		// Sets color from local lighting for leaf node
		if (current->importance < IMPORTANCE_THRESHOLD)
		{
			this->rayTarget(*current);

			current->is_leaf = true;

			current->radiance = this->localLighting(*current);
			current = current->parent;
		}
		// Create child rays if there are none and current isn't a leaf node
		else if (current->children.size() == 0)
		{
			this->rayTarget(*current);

			if (current->target == nullptr) break;	// TODO: Fix the bug that causes this exception

			std::vector<Ray> child_rays = current->target->material->BRDF(current);

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
				current->radiance = this->localLighting(*current);

				for (std::shared_ptr<Ray>& child : current->children)
				{
					current->radiance += child->radiance * child->importance / current->importance * GLOBAL_COLOR_CONTRIBUTION;  
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