#pragma once

/*
We will use this to clean upp the code
*/

#ifndef TYPEDEFS_TNCG15_H //So we wont declare things more than once
#define TYPEDEFS_TNCG15_H

constexpr auto EPSILON = 0.0000000001; //Test

#include <glm/vec3.hpp> //We don't need the whole library

typedef glm::vec3 vec3; // This should be removed after refactor to Vertex
typedef glm::vec3 Vertex;
typedef glm::vec3 Direction;
typedef glm::dvec3 ColorDbl; // R,G,B double precision values

#endif