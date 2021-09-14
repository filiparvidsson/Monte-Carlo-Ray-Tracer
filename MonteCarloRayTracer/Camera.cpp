
#include "Camera.h"

Camera::Camera()
{

	//Camera plane
	corners[0][0] = vec3(0, -1, -1); //Left bottom corner
	corners[0][1] = vec3(0, 1, -1); //Right bottom corner
	corners[1][0] = vec3(0, -1, 1); //Left top corner
	corners[1][1] = vec3(0, 1, 1); //Right top corner

	//Create pixels
}