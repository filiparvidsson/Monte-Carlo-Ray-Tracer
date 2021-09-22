// TNCG15.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "typedefs.h"
#include <glm/glm.hpp>
#include "Triangle.h"
#include "Camera.h"
#include "Ray.h"
//#include "EasyBMP.hpp" //Library for creating BMP image files

int main()
{
    std::cout << "Creating camera...\n";
    vec3 main_observer(-2, 0, 0);
    vec3 sub_observer(-1, 0, 0);
    Camera test_cam(main_observer, sub_observer);
    std::cout << "DONE!\n";

    std::cout << "Creating scene...\n";
    Scene scene;
    std::cout << "DONE!\n";

    std::cout << "Adding sphere...\n";
    scene.addSphere(PURPLE, dvec3(10.0, 0.0, 0.0), 1.0);
    std::cout << "DONE!\n";

    std::cout << "Rendering scene...\n";
    test_cam.render(scene);
    std::cout << "DONE!\n";

    std::cout << "Creating image...\n";
    test_cam.createImage("../Renders/test_image.bmp");
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
