#include "dependencies.h"
#include "EasyBMP.hpp"

float constexpr PIX_DELTA = 0.0025f;
float constexpr PIX_IN_PIX_DELTA = 0.00125f;

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
	std::array<vec3, 4> end_points;

	for (size_t j = 0; j < RESOLUTION; ++j) {
		for (size_t i = 0; i < RESOLUTION; ++i) {

			Pixel& p = getPixel(i, j);
			end_points[0] = vec3(0.0f, static_cast<float>(i) * PIX_DELTA - (1.0f - PIX_DELTA + PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))), static_cast<float>(j) * PIX_DELTA - (1.0f - PIX_DELTA + PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))));
			end_points[1] = vec3(0.0f, static_cast<float>(i) * PIX_DELTA - (1.0f - PIX_DELTA + PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))), static_cast<float>(j) * PIX_DELTA - (1.0f - PIX_DELTA - PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))));
			end_points[2] = vec3(0.0f, static_cast<float>(i) * PIX_DELTA - (1.0f - PIX_DELTA - PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))), static_cast<float>(j) * PIX_DELTA - (1.0f - PIX_DELTA + PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))));
			end_points[3] = vec3(0.0f, static_cast<float>(i) * PIX_DELTA - (1.0f - PIX_DELTA - PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))), static_cast<float>(j) * PIX_DELTA - (1.0f - PIX_DELTA - PIX_IN_PIX_DELTA * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))));
			
			for(vec3 &end : end_points)
			{
				Ray ray{ p_start, end };
				scene.rayTarget(ray);
				std::shared_ptr<Ray> ray_ptr = std::make_shared<Ray>(ray);

				scene.traceRay(ray_ptr);
				p.color += ray_ptr->color / 4.0;
			}

			/*Ray ray{ p_start, p_end };
			scene.rayTarget(ray);
			std::shared_ptr<Ray> ray_ptr = std::make_shared<Ray>(ray);

			scene.traceRay(ray_ptr);
			p.color = ray_ptr->color;*/
		}
	}
}

Pixel& Camera::getPixel(size_t i, size_t j) {
	return (*pixels)[i * RESOLUTION + j];
}

//cramps to dynamic range to be between 0 and 1
void Camera::dynamicRange()
{

	double max_value_r = 0.0;
	double max_value_g = 0.0;
	double max_value_b = 0.0;
	//double min_value = std::numeric_limits<double>::min();


	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {

			Pixel& p = getPixel(i, j);

			if (p.color.x > max_value_r) max_value_r = p.color.x;
			if (p.color.y > max_value_g) max_value_g = p.color.y;
			if (p.color.z > max_value_b) max_value_b = p.color.z;
			
		}
	}

	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {

			Pixel& p = getPixel(i, j);

			p.color.x = p.color.x / (max_value_r);
			p.color.y = p.color.y / (max_value_g);
			p.color.z = p.color.z / (max_value_b);

		}
	}
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
			/*rgb = EasyBMP::RGBColor(static_cast<uint8_t>(p.color.x * 255.99),
				static_cast<uint8_t>(p.color.y * 255.99),
				static_cast<uint8_t>(p.color.z * 255.99));*/
			image.SetPixel(i, j, rgb);
		}
	}
	image.Write();
}