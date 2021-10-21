#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES
#define TYPEDEFS_DEPENDENCIES

// Constants
constexpr auto EPSILON = 1e-4;
constexpr float RAY_OFFSET_AMOUNT = 3e-2f;
constexpr double AIR_REFLECTIVE_INDEX = 1.0f;
constexpr double GLASS_REFLECTIVE_INDEX = 1.5f;
// Settings
constexpr size_t RESOLUTION = 800;
constexpr auto MIN_ABSORPTION = 0.4;
constexpr auto MAX_ABSORPTION = 0.8;
constexpr int MAX_RAY_DEPTH = 12;
constexpr int N_DIFFUSE_BOUNCES = 2;
constexpr int N_SHADOW_RAYS = 2;
constexpr int N_SAMPLES_PIXEL = 100; // Should to be an int^2, e.g 4, 16 or 100
constexpr float IMPORTANCE_THRESHOLD = 0.1f;
constexpr double DIFFUSE_REFLECTANCE = 0.5;
constexpr double GLOBAL_COLOR_CONTRIBUTION = 1.0;
constexpr double DROPOFF_POWER = 1.8;

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
const dvec3 LIGHT_BLUE{ 0.4, 0.7, 1.0 };

// Forward declarations
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