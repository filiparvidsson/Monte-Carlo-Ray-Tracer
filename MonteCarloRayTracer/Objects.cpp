#include "typedefs.h"
#include <iostream>


double Sphere::rayIntersection(Ray& ray) {

	//Intersection for spheres
	//Follows following theroey viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/

	//A = rayStart, B = rayDirection, C = sphereCenter
	//All dot products for the quadratic formula
	dvec3 dotProds;

	dotProds.x = glm::dot(ray.getDirection(), ray.getDirection());
	dotProds.y = 2.0 * glm::dot(ray.getDirection(), ray.getStart() - dvec3(position));
	dotProds.z = glm::dot(ray.getStart() - dvec3(position), ray.getStart() - dvec3(position)) - radius * radius;

	//std::cout << "x: " << dotProds.x << "y: " << dotProds.y << "z: " << dotProds.z << std::endl;

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

Triangle::Triangle(const dvec3& x, const dvec3& y, const dvec3& z, const ColorDbl& col)
	: color{ col }
{
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = z;

	normal = glm::normalize(glm::cross(z - x, y - x));
	edge1 = y - x;
	edge2 = z - x;
		
}

double Triangle::rayIntersection(Ray& ray)
{
	//Möller-Trumbore
	dvec3 T = dvec3(ray.getStart() - vertices[0]);
	dvec3 D = ray.getDirection();
	dvec3 P = glm::cross(D, edge2);
	dvec3 Q = glm::cross(T, edge1);

	dvec3 hit = (1 / glm::dot(P, edge1)) * dvec3(dot(Q, edge2), dot(P, T), dot(Q, D));

	if (hit.x < EPSILON || hit.y < EPSILON || hit.z < EPSILON || hit.z + hit.y > 1.0f) {
		return -1.0;
	}
	else {
		return hit.x;
	}
}

ColorDbl Triangle::getColor()
{
	return color;
}

dvec3 Triangle::getNormal(const dvec3& hit)
{
	return glm::normalize(glm::cross(this->edge1, this->edge2));
}

dvec3 Sphere::getNormal(const dvec3& hit)
{
	return glm::normalize(hit - this->position);
}

Box::Box(const dvec3& pos, double height, double width1, double width2, const ColorDbl& color)
{
	corners[0] = pos + dvec3(width1 * 0.5, width2 * -0.5, height * 0.5);
	corners[1] = pos + dvec3(width1 * -0.5, width2 * -0.5, height * 0.5);
	corners[2] = pos + dvec3(width1 * -0.5, width2 * 0.5, height * 0.5);
	corners[3] = pos + dvec3(width1 * 0.5, width2 * 0.5, height * 0.5);
	corners[4] = pos + dvec3(width1 * 0.5, width2 * -0.5, height * -0.5);
	corners[5] = pos + dvec3(width1 * -0.5, width2 * -0.5, height * -0.5);
	corners[6] = pos + dvec3(width1 * -0.5, width2 * 0.5, height * -0.5);
	corners[7] = pos + dvec3(width1 * 0.5, width2 * 0.5, height * -0.5);

	//Top
	triangles[0] = Triangle(corners[0], corners[3], corners[1], color);
	triangles[1] = Triangle(corners[1], corners[3], corners[2], color);
	//Bottom
	triangles[2] = Triangle(corners[4], corners[5], corners[6], color);
	triangles[3] = Triangle(corners[4], corners[6], corners[7], color);
	//Wall 1
	triangles[4] = Triangle(corners[0], corners[7], corners[3], color);
	triangles[5] = Triangle(corners[0], corners[4], corners[7], color);
	//Wall 2
	triangles[6] = Triangle(corners[0], corners[1], corners[4], color);
	triangles[7] = Triangle(corners[1], corners[5], corners[4], color);
	//Wall 3
	triangles[8] = Triangle(corners[1], corners[2], corners[5], color);
	triangles[9] = Triangle(corners[2], corners[6], corners[5], color);
	//Wall 4
	triangles[10] = Triangle(corners[3], corners[6], corners[2], color);
	triangles[11] = Triangle(corners[3], corners[7], corners[6], color);

}

std::array<Triangle, 12>& Box::getTriangles()
{
	return triangles;
}
