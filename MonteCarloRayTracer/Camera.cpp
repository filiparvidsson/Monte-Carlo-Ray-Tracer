#include "dependencies.h"
#include "EasyBMP.hpp"

float constexpr PIX_DELTA = 0.0025f;

Camera::Camera(vec3 obs1, vec3 obs2)
	: obs1{ obs1 }, obs2{ obs2 }, main_obs{ true }
{
	//Camera plane
	plane[0][0] = vec3(0.0f, -1.0f, -1.0f); //Left bottom corner
	plane[0][1] = vec3(0.0f, 1.0f, -1.0f); //Right bottom corner
	plane[1][0] = vec3(0.0f, -1.0f, 1.0f); //Left top corner
	plane[1][1] = vec3(0.0f, 1.0f, 1.0f); //Right top corner
	pixels = new std::array<Pixel, RESOLUTION* RESOLUTION>();
	pixels->fill(Pixel{ dvec3(0.0, 0.0, 0.0) });
}



void Camera::render(Scene& scene) {

	vec3 p_start = Camera::main_obs ? obs1 : obs2;
	vec3 p_end;

	for (size_t j = 0; j < RESOLUTION; ++j) {
		for (size_t i = 0; i < RESOLUTION; ++i) {

			Pixel& p = getPixel(i, j);
			p_end = vec3(0.0, i * PIX_DELTA - (1.0 - PIX_DELTA), j * PIX_DELTA - (1.0 - PIX_DELTA));
			Ray ray{ p_start, p_end };

			// Iterated through all objects and gets the color of the closest intersection
			double closest_obj = std::numeric_limits<double>::max();
			size_t closest_ind = 0;
			size_t counter = 0;
			for (Object* obj : scene.objects) {
				float hitX = obj->rayIntersection(&ray);
				if (hitX > 0.0 && hitX < closest_obj) {
					closest_obj = hitX;
					closest_ind = counter;
					ray.setEnd(closest_obj);
				}
				++counter;
			}
			ray.AreaLighting(scene, closest_ind);
			p.color = ray.color;
		}
	}
}

Pixel& Camera::getPixel(size_t i, size_t j) {
	return (*pixels)[i * RESOLUTION + j];
}

void Camera::createImage(const char* filepath) {

	EasyBMP::RGBColor rgb(0, 0, 0);
	EasyBMP::Image image(RESOLUTION, RESOLUTION, filepath, rgb);


	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {

			Pixel& p = getPixel(i, j);

			// Truncate the double values with glm::min
			rgb = EasyBMP::RGBColor(static_cast<uint8_t>(glm::min(p.color.x, 1.0) * 255.99),
				static_cast<uint8_t>(glm::min(p.color.y, 1.0) * 255.99),
				static_cast<uint8_t>(glm::min(p.color.z, 1.0) * 255.99));
			image.SetPixel(i, j, rgb);
		}
	}
	image.Write();
}