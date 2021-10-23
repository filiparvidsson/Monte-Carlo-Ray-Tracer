#pragma once
#include "dependencies.h"


struct Pixel {
	
	dvec3 color;
	
	Pixel()
		: color{ BLACK } {};

	Pixel(dvec3 color)
		: color{ color } {};
};