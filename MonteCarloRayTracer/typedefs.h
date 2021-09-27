#pragma once


#ifndef TYPEDEFS_TNCG15_H //So we wont declare things more than once
#define TYPEDEFS_TNCG15_H

constexpr auto EPSILON = 1e-10;

#include <glm/glm.hpp>

typedef glm::dvec3 dvec3;
typedef glm::vec3 vec3;
typedef glm::vec3 Vertex;
typedef glm::vec3 Direction;
typedef glm::dvec3 ColorDbl; //double precision values
typedef glm::ivec3 RGBval; //integer precision values for pixels

//Colors
const ColorDbl RED{ 1.0, 0.0, 0.0 };
const ColorDbl GREEN{ 0.0, 1.0, 0.0 };
const ColorDbl BLUE{ 0.0, 0.0, 1.0 };
const ColorDbl WHITE{ 1.0, 1.0, 1.0 };
const ColorDbl BLACK{ 0.0, 0.0 ,0.0 };
const ColorDbl PURPLE{ 1.0, 0.0, 1.0 };
const ColorDbl YELLOW{ 1.0, 1.0, 0.0 };
const ColorDbl CYAN{ 0.0, 1.0, 1.0 };
const ColorDbl TEAL{ 0.0, 0.5, 0.5 };
const ColorDbl PINK{ 1.0, 0.4, 0.7 };

// Forward declarations
class PointLight;
class Pixel;
class Object;
class Scene;
class Ray;
class Camera;

#include "PointLight.h"
#include "Pixel.h"
#include "Objects.h"
#include "Scene.h"
#include "Ray.h"
#include "Camera.h"
// **********************************************

#endif