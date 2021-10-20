#pragma once
#include "dependencies.h"
#include <iostream>
#include <fstream>
#include <array>


struct Camera {

	vec3 plane[2][2];
	vec3 obs1;
	vec3 obs2;
	bool main_obs;
	std::array<Pixel, RESOLUTION* RESOLUTION>* pixels;

	Camera(vec3 obs1, vec3 obs2);

	// Sends rays from each pixel
	void render(Scene& scene);

	// Creates the output RBG-image
	void createImage(const char* file_path);

	Pixel& getPixel(size_t i, size_t j);

	void toggleObserver() {
		main_obs = !main_obs;
	}
};
