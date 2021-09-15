#ifndef CAMERA_TNCG15_H //So we wont declare things more than once
#define CAMERA_TNCG15_H
#include "typedefs.h"
#include "Pixel.h"
#include "Ray.h"
//#include "EasyBMP.hpp"
#include "Ray.h"
#include "Scene.h"
#include <vector>
#include <iostream>
#include <fstream>

int constexpr RESOLUTION = 800;

class Camera {
public:
	Camera();
	
	~Camera() {};

	// Sends rays from each pixel
	void render();

	// Creates the output RBG-image
	void createImage();

	void createImage2(Scene& scene);

private:
	Vertex plane[2][2];
	Vertex observer;
	//Pixel pixels[RESOLUTION][RESOLUTION]; //Too big for stack, use EasyBMP instead
	float pixel_delt;
};

#endif