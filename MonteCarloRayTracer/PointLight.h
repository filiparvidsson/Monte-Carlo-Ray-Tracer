#pragma once

#include "typedefs.h"


struct PointLight {

	PointLight(vec3 pos, double intens, ColorDbl col)
		: position{ pos }, intensity{ intens }, color{ col } {};

	vec3 position;
	double intensity;
	ColorDbl color;
};