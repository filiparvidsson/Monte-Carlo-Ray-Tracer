#include "Camera.h"

float constexpr DELTA = 0.0025f;

Camera::Camera()
{
	//Camera plane
	plane[0][0] = Vertex(0, -1, -1); //Left bottom corner
	plane[0][1] = Vertex(0, 1, -1); //Right bottom corner
	plane[1][0] = Vertex(0, -1, 1); //Left top corner
	plane[1][1] = Vertex(0, 1, 1); //Right top corner

	observer = Vertex(-2, 0, 0); // Default, should be able to switch to (-1,0,0)

	pixel_delt = DELTA;
}

void Camera::render() {

}

void Camera::createImage() {

	// Test render 
	FILE* out_img = fopen("../Renders/out_img.bmp", "w");
	
	for (int i = 0; i < RESOLUTION; ++i) {
		for (int j = 0; j < RESOLUTION; ++j) {
			fwrite(&i, 1, 1, out_img);
			fwrite(&j, 1, 1, out_img);
		}	
	}

	fclose(out_img);
}