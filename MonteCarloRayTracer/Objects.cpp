#include "Objects.h"
#include <iostream>

double Sphere::rayIntersection(Ray& ray) {

	//Intersection for spheres
	//Follows following theroey viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/

	//A = rayStart, B = rayDirection, C = sphereCenter
	//All dot products for the quadratic formula
	dvec3 dotProds;

	dotProds.x = glm::dot(ray.getDirection(), ray.getDirection());
	dotProds.y = 2.0 * glm::dot(ray.getDirection(), ray.getStart() - vec3(position));
	dotProds.z = glm::dot(ray.getStart() - vec3(position), ray.getStart() - vec3(position)) - radius * radius;

	std::cout << "x: " << dotProds.x << "y: " << dotProds.y << "z: " << dotProds.z << std::endl;

	//The dicriminant which check for hits
	double discriminant = dotProds.y * dotProds.y - 4 * dotProds.x * dotProds.z;

	//If determinant < 0: No hit, If ==0, It scraped along the surface
	if (discriminant < EPSILON) {
		return -1.0;
	}
	else {
		double numerator = -dotProds.y + sqrt(discriminant);

		if (numerator > 0.0) { //Check if hit was behind camera, we dont want that
			return numerator / (2.0 * dotProds.x);
		}
		//Check both possibilities since its +-sqrt
		numerator = -dotProds.y - sqrt(discriminant);

		if (numerator > 0.0) {
			return numerator / (2.0 * dotProds.x);
		}
		else {
			return -1.0;
		}

	return -1.0;
	}
	


}

ColorDbl Sphere::getColor()
{
	return color;
}
