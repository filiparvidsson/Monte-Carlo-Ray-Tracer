#ifndef SCENE_TNCG15_H //So we wont declare things more than once
#define SCENE_TNCG15_H

#include <glm/glm.hpp>
#include <vector>
#include "typedefs.h"
#include "Triangle.h"

/*

    (1)--------(6)
    /            \
(2)/              \(5)
   \    Bottom    /
    \            /
    (3)--------(4)

    (7)--------(12)
    /            \
(8)/              \(11)
   \    Top       /
    \            /
    (9)--------(10)
*/

//Colors
const ColorDbl RED = ColorDbl(1.0, 0.0, 0.0);
const ColorDbl GREEN = ColorDbl(0.0, 1.0, 0.0);
const ColorDbl BLUE = ColorDbl(0.0, 0.0, 1.0);
const ColorDbl WHITE = ColorDbl(1.0, 1.0, 1.0);

//Bottom
const vec3 P1 = vec3(6.0f, 0.0f, -5.0f);
const vec3 P2 = vec3(-3.0f, 0.0f, -5.0f);
const vec3 P3 = vec3(0.0f, -6.0f, -5.0f);
const vec3 P4 = vec3(10.0f, -6.0f, -5.0f);
const vec3 P5 = vec3(13.0f, 0.0f, -5.0f);
const vec3 P6 = vec3(10.0f, -6.0f, -5.0f);

//Top
const vec3 P7 = vec3(6.0f, 0.0f, 5.0f);
const vec3 P8 = vec3(-3.0f, 0.0f, 5.0f);
const vec3 P9 = vec3(0.0f, -6.0f, 5.0f);
const vec3 P10 = vec3(10.0f, -6.0f, 5.0f);
const vec3 P11 = vec3(13.0f, 0.0f, 5.0f);
const vec3 P12 = vec3(10.0f, -6.0f, 5.0f);

//Bottom
Triangle triangle1 = Triangle(P1, P2, P3, WHITE);
Triangle triangle2 = Triangle(P4, P5, P6, WHITE);
Triangle triangle3 = Triangle(P1, P3, P6, WHITE);
Triangle triangle4 = Triangle(P3, P4, P6, WHITE);


//Top
Triangle triangle5 = Triangle(P9, P8, P7, WHITE);
Triangle triangle6 = Triangle(P12, P11, P10, WHITE);
Triangle triangle7 = Triangle(P9, P7, P12, WHITE);
Triangle triangle8 = Triangle(P9, P12, P10, WHITE);

//Wall 1
Triangle triangle9 = Triangle(P3, P9, P10, RED);
Triangle triangle10 = Triangle(P3, P10, P4, RED);

//Wall 2
Triangle triangle11 = Triangle(P10, P11, P4, BLUE);
Triangle triangle12 = Triangle(P11, P5, P4, BLUE);

//Wall 3
Triangle triangle13 = Triangle(P11, P12, P5, GREEN);
Triangle triangle14 = Triangle(P12, P6, P5, GREEN);

//Wall 4
Triangle triangle13 = Triangle(P12, P7, P6, RED);
Triangle triangle14 = Triangle(P7, P1, P6, RED);

//Wall 5
Triangle triangle15 = Triangle(P7, P8, P1, BLUE);
Triangle triangle16 = Triangle(P1, P2, P8, BLUE);

//Wall 6
Triangle triangle17 = Triangle(P2, P8, P9, GREEN);
Triangle triangle18 = Triangle(P2, P9, P3, GREEN);

class Scene {

public:
	Scene();

    void loadTriangles();

private:
	std::vector<Triangle> triangles;

};

#endif