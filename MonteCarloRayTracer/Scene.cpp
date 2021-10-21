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
	dvec3 final_color = BLACK;

	if (ray.target == nullptr) return final_color;

	if (ray.target->material->emittance != 0.0) {
		return ray.target->material->color;
	}

	//According to Lesson
	for (Object* light_source : this->area_lights) {

		dvec3 this_light = BLACK;

		vec3 end_offset = ray.end + ray.target->getNormal(ray.end) * RAY_OFFSET_AMOUNT;
		std::vector<Ray> shadow_rays = light_source->generateShadowRays(end_offset);

		for (Ray& sr : shadow_rays) {

			bool occluded = false;
			float target_length = glm::length(sr.end - sr.start);

			vec3 targetNormal = ray.target->getNormal(ray.end);
			vec3 lightNormal = light_source->getNormal(sr.end);

			double beta = glm::dot(-sr.direction, lightNormal);
			double alpha = glm::dot(targetNormal, sr.direction);
			double cos_term = alpha * beta;
			cos_term = glm::max(cos_term, 0.0);

			for (Object* shadow_object : this->objects) {
				
				Ray temp = sr;
				// Is shadow_object not a light source or transparent object
				if (dynamic_cast<Light*>(shadow_object->material) == nullptr && dynamic_cast<Glass*>(shadow_object->material) == nullptr) {
					float hit_x = shadow_object->rayIntersection(&sr);
					
					temp.setEnd(hit_x);

					if (hit_x > EPSILON && glm::length(temp.end - temp.start) < target_length) {
						occluded = true;
						break;
					}
				}
			}
			// Ray intersection is occluded if the intersected ray is shorter than the original ray
			if (!occluded) {
				double dropoff = glm::pow(glm::length(sr.end - sr.start), 2);
				this_light += light_source->material->emittance * cos_term * light_source->material->color / (dropoff * area_lights.size());
			}
		}
		final_color += this_light / static_cast<double>(shadow_rays.size());
	} 
	return final_color * ray.target->material->color;
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