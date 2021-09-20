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

    std::cout << "Rendering scene...\n";
    test_cam.render(scene);
    std::cout << "DONE!\n";

    std::cout << "Creating image...\n";
    test_cam.createImage("../Renders/test_image.bmp");
    std::cout << "DONE!\n";
    std::cout << "Exiting program...\n";



    ////Triangle soup;
    //std::cout << "Hello World!\n";

    //Camera test;
    //std::cout << "camera is created" << std::endl;
    //Scene scene;
    //std::cout << "scene is created" << std::endl;
    //test.createImage2(scene);

    //EasyBMP::RGBColor black(0, 0, 0);
    //// sizeX, sizeY, FileName, BackgroundColor
    //EasyBMP::Image img(800, 800, "sample2.bmp", black);

    //vec3 eye = vec3(-1.0, 0.0, 0.0);
    //vec3 endPoint = vec3();
    //int final_colorR = 250;
    //int final_colorB = 250;
    //int final_colorG = 250;

    //Ray ray = Ray(eye, endPoint); //Write to image
    ///*for (int y = 0; y < 800; ++y) {
    //    for (int x = 0; x < 800; ++x) {

    //        endPoint = vec3(0.0, x*0.0025 - 0.99875, y * 0.0025 - 0.99875);
    //        ray = Ray(eye, endPoint);
    //        for (int i = 0; i < scene.getTriangles().size(); ++i) {
    //            if (scene.getTriangles()[i].rayIntersection(ray)) {
    //                final_colorR = (int)scene.getTriangles()[i].getColor().x;
    //                final_colorG = (int) scene.getTriangles()[i].getColor().y;
    //                final_colorB = (int) scene.getTriangles()[i].getColor().z;

    //               // std::cout << "Ray found triangle" << std::endl;

    //                break;
    //            }
    //        }
    //        //assert()
    //        
    //        // PositionX, PisitionY, Color
    //        img.SetPixel(x, y, EasyBMP::RGBColor(final_colorR*255, final_colorG * 255, final_colorB * 255));
    //    
    //}
    //img.Write();
    //*/
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
