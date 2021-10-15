#pragma once
#include "dependencies.h"


struct Pixel {
	
	dvec3 color;

	//Ray passingRay;
	
	Pixel()
		: color{ dvec3(0.0, 0.0, 0.0) } {};

	Pixel(dvec3 clr)
		: color{ clr } {};



};