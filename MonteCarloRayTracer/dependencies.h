#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES
#define TYPEDEFS_DEPENDENCIES

// Constants
constexpr auto EPSILON = 1e-4;
constexpr float RAY_OFFSET_AMOUNT = 3e-2f;
// Settings
constexpr int MAX_RAY_DEPTH = 10;
constexpr auto MIN_ABSORPTION = 0.65;
constexpr auto MAX_ABSORPTION = 0.90;
constexpr float IMPORTANCE_THRESHOLD = 0.1f;
constexpr int N_DIFFUSE_BOUNCES = 1;
constexpr int N_SHADOW_RAYS = 1;
constexpr int N_SAMPLES_PIXEL = 4; // Needs to be an int^2
constexpr size_t RESOLUTION = 800;
constexpr double DIFFUSE_REFLECTANCE = 0.2;
constexpr double GLOBAL_COLOR_CONTRIBUTION = 0.3;

#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include <chrono>
#include <thread>

typedef glm::dvec3 dvec3;
typedef glm::vec3 vec3;

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

#include "Pixel.h"
#include "Objects.h"
#include "Scene.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"
#include <stdlib.h>
#include <math.h>

#endif