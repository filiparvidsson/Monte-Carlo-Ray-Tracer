#include "dependencies.h"
#include "EasyBMP.hpp"


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

	vec3 start = Camera::main_obs ? obs1 : obs2;

	int pixel_dimensions = sqrt(N_SAMPLES_PIXEL);
	float pixel_size{ glm::distance(this->plane[0][0], this->plane[0][1]) / RESOLUTION };
	float pixel_sample_size{ pixel_size / pixel_dimensions };

	for (size_t j = 0; j < RESOLUTION; ++j) {
		for (size_t i = 0; i < RESOLUTION; ++i) {

			Pixel& p = getPixel(i, j);
			

			for (int k = 0; k < N_SAMPLES_PIXEL; ++k)
			{
				float x_end = static_cast<float>(i) * pixel_size - (1.0f - pixel_size) + static_cast<float>(k % pixel_dimensions) * pixel_sample_size;
				float y_end = static_cast<float>(j) * pixel_size - (1.0f - pixel_size) + static_cast<float>(floor((k / pixel_dimensions))) * pixel_sample_size;

				x_end += static_cast<float>(rand() / RAND_MAX) * pixel_sample_size;
				y_end += static_cast<float>(rand() / RAND_MAX) * pixel_sample_size;

				vec3 end{ 0.0f, x_end, y_end };

				Ray ray{ start, end };
				scene.rayTarget(ray);
				std::shared_ptr<Ray> ray_ptr = std::make_shared<Ray>(ray);

				scene.traceRay(ray_ptr);
				p.color += ray_ptr->color / static_cast<double>(N_SAMPLES_PIXEL);
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

	double max_intensity = 0.0;
	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {
			
			Pixel& p = getPixel(i, j);

			p.color = glm::sqrt(p.color);

			if (p.color.r > max_intensity)
				max_intensity = p.color.r;
			if (p.color.g > max_intensity)
				max_intensity = p.color.g;
			if (p.color.b > max_intensity)
				max_intensity = p.color.b;
		}
	}

	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {

			Pixel& p = getPixel(i, j);

			rgb = EasyBMP::RGBColor(static_cast<uint8_t>(p.color.r * 255.99 / max_intensity),
									static_cast<uint8_t>(p.color.g * 255.99 / max_intensity),
									static_cast<uint8_t>(p.color.b * 255.99 / max_intensity));
			
			image.SetPixel(i, j, rgb);
		}
	}

	image.Write();
}