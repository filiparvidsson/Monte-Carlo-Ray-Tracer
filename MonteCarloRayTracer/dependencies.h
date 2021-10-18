#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES //So we wont declare things more than once
#define TYPEDEFS_DEPENDENCIES

//Constants
constexpr auto EPSILON = 1e-8;
constexpr int SHADOWSAMPLES = 1;
constexpr auto MIN_REFLECTANCE = 0.3;
constexpr auto MAX_REFLECTANCE = 0.65;
constexpr float IMPORTANCE_THRESHOLD = 0.2f;
constexpr float RAY_OFFSET_AMOUNT = 3e-2f;
constexpr int MAX_RAY_DEPTH = 15;
constexpr int N_DIFFUSE_BOUNCES = 1;

#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <cstdlib>
#include <math.h>

typedef glm::dvec3 dvec3; //Mainly for Colors
typedef glm::vec3 vec3;
typedef glm::ivec3 RGBval; //integer precision values for pixels

//Colors
const dvec3 RED{ 1.0, 0.0, 0.0 };
const dvec3 GREEN{ 0.0, 1.0, 0.0 };
const dvec3 BLUE{ 0.0, 0.0, 1.0 };
const dvec3 WHITE{ 1.0, 1.0, 1.0 };
const dvec3 BLACK{ 0.0, 0.0 ,0.0 };
const dvec3 PURPLE{ 1.0, 0.0, 1.0 };
const dvec3 YELLOW{ 1.0, 1.0, 0.0 };
const dvec3 CYAN{ 0.0, 1.0, 1.0 };
const dvec3 TEAL{ 0.0, 0.5, 0.5 };
const dvec3 PINK{ 1.0, 0.4, 0.7 };

// Forward declarations
//struct PointLight;
struct Pixel;
struct Object;
struct Scene;
struct Ray;
struct Camera;
struct Material;


#include "PointLight.h"
#include "Pixel.h"
#include "Objects.h"
#include "Scene.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include <stdlib.h>
#include <math.h>



// **********************************************

#endif