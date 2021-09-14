#ifndef CAMERA_TNCG15_H //So we wont declare things more than once
#define CAMERA_TNCG15_H
#include "typedefs.h"

class Camera {
public:
	Camera();
	~Camera() {};

	

private:
	//[rad][kolumn]
	vec3 corners[2][2];

};

#endif