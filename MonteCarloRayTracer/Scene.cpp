
#include "Scene.h"
#include "typedefs.h"

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

//Bottom
const vec3 P1 = vec3(6.0, 0.0, -5.0);
const vec3 P2 = vec3(-3.0, 0.0, -5.0);
const vec3 P3 = vec3(0.0, -6.0, -5.0);
const vec3 P4 = vec3(10.0, -6.0, -5.0);
const vec3 P5 = vec3(13.0, 0.0, -5.0);
const vec3 P6 = vec3(10.0, -6.0, -5.0);

//Top
const vec3 P7 = vec3(6.0, 0.0, 5.0);
const vec3 P8 = vec3(-3.0, 0.0, 5.0);
const vec3 P9 = vec3(0.0, -6.0, 5.0);
const vec3 P10 = vec3(10.0, -6.0, 5.0);
const vec3 P11 = vec3(13.0, 0.0, 5.0);
const vec3 P12 = vec3(10.0, -6.0, 5.0);

//Bottom
Triangle triangle1 = Triangle(P1, P2, P3);
Triangle triangle2 = Triangle(P4, P5, P6);
Triangle triangle3 = Triangle(P1, P3, P6);
Triangle triangle4 = Triangle(P3, P4, P6);

//Top
Triangle triangle5 = Triangle(P9, P8, P7);
Triangle triangle6 = Triangle(P12, P11, P10);
Triangle triangle7 = Triangle(P9, P7, P12);
Triangle triangle8 = Triangle(P9, P12, P10);

//Wall 1
Triangle triangle9 = Triangle(P3, P9, P10);
Triangle triangle10 = Triangle(P3, P10, P4);

//Wall 2
Triangle triangle11 = Triangle(P10, P11, P4);
Triangle triangle12 = Triangle(P11, P5, P4);

//Wall 3
Triangle triangle13 = Triangle(P11, P12, P5);
Triangle triangle14 = Triangle(P12, P6, P5);

//Wall 4
Triangle triangle13 = Triangle(P12, P7, P6);
Triangle triangle14 = Triangle(P7, P1, P6);

//Wall 5
Triangle triangle15 = Triangle(P7, P8, P1);
Triangle triangle16 = Triangle(P1, P2, P8);

//Wall 6
Triangle triangle17 = Triangle(P2, P8, P9);
Triangle triangle18 = Triangle(P2, P9, P3);



Scene::Scene()
{

}

