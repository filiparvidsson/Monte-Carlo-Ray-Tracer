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
			p_end = vec3(0.0f, static_cast<float>(i) * PIX_DELTA - (1.0f - PIX_DELTA), static_cast<float>(j) * PIX_DELTA - (1.0f - PIX_DELTA));
			
			Ray ray{ p_start, p_end };
			scene.rayTarget(ray);
			std::shared_ptr<Ray> ray_ptr = std::make_shared<Ray>(ray);

			// I don't know why but sometimes we can't find a target, need this check
			if (ray.target != nullptr)
			{
				scene.traceRay(ray_ptr);

				p.color = ray_ptr->color;
			}
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