#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES
#define TYPEDEFS_DEPENDENCIES

//-------- Libraries ----------
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

//------- Definitions ---------
typedef glm::dvec3 dvec3;
typedef glm::vec3 vec3;

//-------- Constants ----------
constexpr auto EPSILON = 1e-4;
constexpr float RAY_OFFSET_AMOUNT = 3e-2f;
//--------- Settings ----------
constexpr size_t RESOLUTION = 800;
constexpr int MAX_RAY_DEPTH = 12;
constexpr int N_DIFFUSE_BOUNCES = 1;
constexpr int N_SHADOW_RAYS = 1;
constexpr int N_SAMPLES_PIXEL = 4; // Should to be an int^2, e.g 4, 16 or 100
constexpr float AIR_REFLECTIVE_INDEX = 1.0f;
constexpr float GLASS_REFLECTIVE_INDEX = 1.5f;
constexpr double IMPORTANCE_THRESHOLD = 0.1;
constexpr double GLOBAL_COLOR_CONTRIBUTION = 1.0;
constexpr double DROPOFF_POWER = 2.0;
constexpr double DIFFUSE_REFLECTANCE = 0.9;
constexpr double MIN_DIFFUSE_ABSORPTION = 1.2;	// > 1.0
constexpr double MAX_DIFFUSE_ABSORPTION = 1.8;

//---------- Colors -----------
constexpr dvec3 WHITE{ 1.0, 1.0, 1.0 };
constexpr dvec3 DARK_GRAY{ 0.25, 0.25, 0.25 };
constexpr dvec3 BLACK{ 0.0, 0.0 ,0.0 };
constexpr dvec3 RED{ 1.0, 0.0, 0.0 };
constexpr dvec3 GREEN{ 0.0, 1.0, 0.0 };
constexpr dvec3 BLUE{ 0.0, 0.0, 1.0 };
constexpr dvec3 LIGHT_BLUE{ 0.0, 0.0, 0.1 };
constexpr dvec3 CYAN{ 0.0, 1.0, 1.0 };
constexpr dvec3 TEAL{ 0.0, 0.5, 0.5 };
constexpr dvec3 PURPLE{ 1.0, 0.0, 1.0 };
constexpr dvec3 DARK_PURPLE{ 0.5, 0.0, 0.5 };
constexpr dvec3 YELLOW{ 1.0, 1.0, 0.0 };
constexpr dvec3 PINK{ 1.0, 0.4, 0.7 };

//--- Forward declarations ----
struct Pixel;
struct Object;
struct Scene;
struct Ray;
struct Camera;
struct Material;

//---------- Files ------------
#include "Pixel.h"
#include "Objects.h"
#include "Scene.h"
#include "Ray.h"
#include "Camera.h"
#include "Material.h"

#endif