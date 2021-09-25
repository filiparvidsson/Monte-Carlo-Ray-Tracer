#include "Camera.h"
#include "EasyBMP.hpp"

double constexpr PIX_DELTA = 0.0025;

Camera::Camera(Vertex obs1, Vertex obs2)
	: obs1{obs1}, obs2{obs2}, main_obs{ true }
{
	//Camera plane
	plane[0][0] = Vertex(0, -1, -1); //Left bottom corner
	plane[0][1] = Vertex(0, 1, -1); //Right bottom corner
	plane[1][0] = Vertex(0, -1, 1); //Left top corner
	plane[1][1] = Vertex(0, 1, 1); //Right top corner
	pixels = new std::array<Pixel, RESOLUTION * RESOLUTION>();
	pixels->fill(Pixel{ ColorDbl(0.0, 0.0, 0.0) });
}

void Camera::render(Scene& scene) {

	vec3 p_start = Camera::main_obs ? obs1 : obs2;
	vec3 p_end;
	Ray ray;

	for (size_t j = 0; j < RESOLUTION; ++j) {
		for (size_t i = 0; i < RESOLUTION; ++i) {
			
			Pixel& p = getPixel(i, j);
			p_end = vec3(0.0, i*PIX_DELTA-(1.0-PIX_DELTA), j*PIX_DELTA-(1.0-PIX_DELTA));
			ray = Ray(p_start, p_end);
			
			// Iterated through all objects and gets the color of the closest intersection
			double closestObj = std::numeric_limits<double>::max();
			for (Object* obj : scene.getObjects()) {

				double hitX = obj->rayIntersection(ray);

				if (hitX > 0.0 && hitX < closestObj) {
					closestObj = hitX;
					p.color = obj->getColor();
				}
			}
		}
	}
}

void Camera::createImage(const char* filepath) {

	EasyBMP::RGBColor rgb(0, 0, 0);
	EasyBMP::Image image(RESOLUTION, RESOLUTION, filepath, rgb);

	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {

			Pixel& p = getPixel(i, j);

			rgb = EasyBMP::RGBColor(static_cast<uint8_t>(p.color.x*255.99), static_cast<uint8_t>(p.color.y * 255.99), static_cast<uint8_t>(p.color.z * 255.99));
			image.SetPixel(i, j, rgb);
		}
	}
	image.Write();
}

Pixel& Camera::getPixel(size_t i, size_t j) {
	return (*pixels)[i * RESOLUTION + j];
}

