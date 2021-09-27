#pragma once

#include "typedefs.h"


class PointLight {
public:
	PointLight(dvec3 pos, double intens, ColorDbl col)
		: position{ pos }, intensity{ intens }, color{ col } {};

	dvec3 position;
	double intensity;
	ColorDbl color;
};