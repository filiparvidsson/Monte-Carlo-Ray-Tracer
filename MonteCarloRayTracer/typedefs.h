#pragma once

/*
We will use this to clean upp the code
*/

#ifndef TYPEDEFS_TNCG15_H //So we wont declare things more than once
#define TYPEDEFS_TNCG15_H

constexpr auto EPSILON = 1e-10;

#include <glm/vec3.hpp> //We don't need the whole library

typedef glm::dvec3 dvec3;
typedef glm::vec3 vec3;
typedef glm::vec3 Vertex;
typedef glm::vec3 Direction;
typedef glm::dvec3 ColorDbl; //double precision values
typedef glm::ivec3 RGBval; //integer precision values for pixels

//Colors
const ColorDbl RED = ColorDbl(1.0, 0.0, 0.0);
const ColorDbl GREEN = ColorDbl(0.0, 1.0, 0.0);
const ColorDbl BLUE = ColorDbl(0.0, 0.0, 1.0);
const ColorDbl WHITE = ColorDbl(1.0, 1.0, 1.0);
const ColorDbl PURPLE = ColorDbl(1.0, 0.0, 1.0);
const ColorDbl YELLOW{ 1.0, 1.0, 0.0 };

#endif