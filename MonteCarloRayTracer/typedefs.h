#pragma once

/*
We will use this to clean upp the code
*/

#ifndef TYPEDEFS_TNCG15_H //So we wont declare things more than once
#define TYPEDEFS_TNCG15_H

constexpr auto EPSILON = 0.0000000000001;

#include <glm/vec3.hpp> //We don't need the whole library

typedef glm::vec3 vec3;
typedef glm::vec3 Vertex;
typedef glm::vec3 Direction;
typedef glm::dvec3 ColorDbl; //double precision values
typedef glm::ivec3 RGBval; //integer precision values for pixels

#endif