#ifndef CAMERA_TNCG15_H //So we wont declare things more than once
#define CAMERA_TNCG15_H

#include "typedefs.h"
#include "Pixel.h"
#include "Ray.h"
#include "Scene.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <array>

size_t constexpr RESOLUTION = 800;

class Camera {
public:

	Camera(Vertex obs1, Vertex obs2);

	// Sends rays from each pixel
	void render(Scene& scene);

	// Creates the output RBG-image
	void createImage(const char* file_name);

	Pixel& getPixel(size_t i, size_t j);

private:
	Vertex plane[2][2];
	Vertex obs1;
	Vertex obs2;
	bool main_obs;
	std::array<Pixel, RESOLUTION * RESOLUTION>* pixels;
};

#endif