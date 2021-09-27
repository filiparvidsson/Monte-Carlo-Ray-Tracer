// TNCG15.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
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

int main()
{
    std::cout << "Creating camera...\n";
    dvec3 main_observer(-2, 0, 0);
    dvec3 sub_observer(-1, 0, 0);
    Camera test_cam(main_observer, sub_observer);
    std::cout << "DONE!\n";

    std::cout << "Changing to secondary observer...\n";
    test_cam.toggleObserver();
    std::cout << "DONE!\n";

    std::cout << "Creating scene...\n";
    Scene scene;
    std::cout << "DONE!\n";

    std::cout << "Setting up room...\n";
    //Bottom
    const dvec3 P1(0.0f, 6.0f, -5.0f); // = vec3(0.0f, 6.0f, -5.0f);
    const dvec3 P2 = dvec3(-3.0f, 0.0f, -5.0f);
    const dvec3 P3 = dvec3(0.0f, -6.0f, -5.0f);
    const dvec3 P4 = dvec3(10.0f, -6.0f, -5.0f);
    const dvec3 P5 = dvec3(13.0f, 0.0f, -5.0f);
    const dvec3 P6 = dvec3(10.0f, 6.0f, -5.0f);

    //Top
    const dvec3 P7 = dvec3(0.0f, 6.0f, 5.0f);
    const dvec3 P8 = dvec3(-3.0f, 0.0f, 5.0f);
    const dvec3 P9 = dvec3(0.0f, -6.0f, 5.0f);
    const dvec3 P10 = dvec3(10.0f, -6.0f, 5.0f);
    const dvec3 P11 = dvec3(13.0f, 0.0f, 5.0f);
    const dvec3 P12 = dvec3(10.0f, 6.0f, 5.0f);

    //Bottom
    Triangle triangle1 = Triangle(P1, P2, P3, PURPLE);
    Triangle triangle2 = Triangle(P4, P5, P6, PURPLE);
    Triangle triangle3 = Triangle(P1, P3, P6, PURPLE);
    Triangle triangle4 = Triangle(P3, P4, P6, PURPLE);


    //Top
    Triangle triangle5 = Triangle(P9, P8, P7, WHITE);
    Triangle triangle6 = Triangle(P12, P11, P10, WHITE);
    Triangle triangle7 = Triangle(P9, P7, P12, WHITE);
    Triangle triangle8 = Triangle(P9, P12, P10, WHITE);

    //Wall 1
    Triangle triangle9 = Triangle(P3, P9, P10, CYAN);
    Triangle triangle10 = Triangle(P3, P10, P4, CYAN);

    //Wall 2
    Triangle triangle11 = Triangle(P10, P11, P4, BLUE);
    Triangle triangle12 = Triangle(P11, P5, P4, BLUE);

    //Wall 3
    Triangle triangle13 = Triangle(P11, P12, P5, GREEN);
    Triangle triangle14 = Triangle(P12, P6, P5, GREEN);

    //Wall 4
    Triangle triangle15 = Triangle(P12, P7, P6, RED);
    Triangle triangle16 = Triangle(P7, P1, P6, RED);

    //Wall 5
    Triangle triangle17 = Triangle(P7, P8, P1, WHITE);
    Triangle triangle18 = Triangle(P1, P2, P8, WHITE);

    //Wall 6
    Triangle triangle19 = Triangle(P2, P8, P9, WHITE);
    Triangle triangle20 = Triangle(P2, P9, P3, WHITE);

    scene.addObject(&triangle1);
    scene.addObject(&triangle2);
    scene.addObject(&triangle3);
    scene.addObject(&triangle4);
    scene.addObject(&triangle5);
    scene.addObject(&triangle6);
    scene.addObject(&triangle7);
    scene.addObject(&triangle8);
    scene.addObject(&triangle9);
    scene.addObject(&triangle10);
    scene.addObject(&triangle11);
    scene.addObject(&triangle12);
    scene.addObject(&triangle13);
    scene.addObject(&triangle14);
    scene.addObject(&triangle15);
    scene.addObject(&triangle16);
    scene.addObject(&triangle17);
    scene.addObject(&triangle18);
    scene.addObject(&triangle19);
    scene.addObject(&triangle20);
    std::cout << "Number of objects: " << scene.getObjects().size() << std::endl;
    std::cout << "DONE!\n";

    std::cout << "Adding teal sphere...\n";
    Sphere s1{ dvec3(8.0, 1.0, 0.0), 1.0, TEAL };
    scene.addObject(&s1);
    std::cout << "Number of objects: " << scene.getObjects().size() << std::endl;
    std::cout << "DONE!\n";

    std::cout << "Adding yellow sphere...\n";
    Sphere s2{ dvec3(10.0, -1.0, -0.5), 1.3, YELLOW };
    scene.addObject(&s2);
    std::cout << "Number of objects: " << scene.getObjects().size() << std::endl;
    std::cout << "DONE!\n";

    std::cout << "Adding white point light...\n";
    PointLight pl1{ dvec3(8.0, -4.0, -4.0), 1.0, WHITE };
    scene.addPointLight(pl1);
    std::cout << "Number of point lights: " << scene.getPointLights().size() << std::endl;
    std::cout << "DONE!\n";

    //std::cout << "Adding pink point light...\n";
    //PointLight pl2{ dvec3(6.0, -4.0, 0.0), 0.4, PINK };
    //scene.addPointLight(pl2);
    //std::cout << "Number of point lights: " << scene.getPointLights().size() << std::endl;
    //std::cout << "DONE!\n";

    std::cout << "Adding white spherical area light...\n";
    Sphere al1{ dvec3(9.0, -5.0, 0.0), 0.7, WHITE };
    scene.addAreaLight(&al1);
    std::cout << "Number of area lights: " << scene.getAreaLights().size() << std::endl;
    std::cout << "DONE!\n";

    std::cout << "Rendering scene...\n";
    test_cam.render(scene);
    std::cout << "DONE!\n";

    std::cout << "Creating image...\n";
    test_cam.createImage("../Renders/shadow_1.bmp");
    std::cout << "DONE!\n";
    std::cout << "Exiting program...\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
