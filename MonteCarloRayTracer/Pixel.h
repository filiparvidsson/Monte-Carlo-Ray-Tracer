
#ifndef PIXEL_TNCG15_H //So we wont declare things more than once
#define PIXEL_TNCG15_H
#include "typedefs.h"
#include "Ray.h"

class Pixel {
public:
	Pixel();

private:

	ColorDbl color;
	Ray passingRay;

};

#endif
