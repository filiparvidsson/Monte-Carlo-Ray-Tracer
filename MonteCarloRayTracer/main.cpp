// TNCG15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "EasyBMP.hpp" //Library for creating BMP image files
#include <iostream>
#include "typedefs.h"
#include <glm/glm.hpp>
#include "Triangle.h"
#include "Camera.h"

int main()
{
    //Triangle soup;
    std::cout << "Hello World!\n";

    Camera test;
    std::cout << "camera is created" << std::endl;
    Scene scene;
    std::cout << "scene is created" << std::endl;
    test.createImage2(scene);

    EasyBMP::RGBColor black(0, 0, 0);
    // sizeX, sizeY, FileName, BackgroundColor
    EasyBMP::Image img(800, 800, "sample.bmp", black);

    for (int y = 0; y < 800; ++y) {
        for (int x = 0; x < 800; ++x) {
            double intensity = 0.0;
            
            int final_color = 250;
            // PositionX, PisitionY, Color
            img.SetPixel(x, y, EasyBMP::RGBColor(final_color, 0, 0));
        }
    }
    img.Write();

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
