#ifndef CAMERA_TNCG15_H //So we wont declare things more than once
#define CAMERA_TNCG15_H

#include "typedefs.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <array>


size_t constexpr RESOLUTION = 800;

class Camera {
public:

	Camera( dvec3 obs1, dvec3 obs2 );

	// Sends rays from each pixel
	void render(Scene& scene);

	// Creates the output RBG-image
	void createImage(const char* file_path);

	Pixel& getPixel(size_t i, size_t j);

	void toggleObserver() {
		main_obs = !main_obs;
	}

private:
	dvec3 plane[2][2];
	dvec3 obs1;
	dvec3 obs2;
	bool main_obs;
	std::array<Pixel, RESOLUTION * RESOLUTION>* pixels;
};

#endif