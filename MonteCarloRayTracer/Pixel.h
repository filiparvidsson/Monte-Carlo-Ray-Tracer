#ifndef PIXEL_TNCG15_H //So we wont declare things more than once
#define PIXEL_TNCG15_H
#include "typedefs.h"
#include "Ray.h"

class Pixel {
public:
	Pixel()
		: color{ ColorDbl(0.0, 0.0, 0.0) } {};

	Pixel(ColorDbl clr)
		: color{ clr } {};

	ColorDbl color;
private:

	//Ray passingRay;

};

#endif
