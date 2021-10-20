#include "dependencies.h"


int main()
{
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

    std::cout << "Current settings: \n";
    std::cout << "\t-Number of shadow rays: " << N_SHADOW_RAYS << "\n";
    std::cout << "\t-Number of bounces on diffuse surfaces: " << N_DIFFUSE_BOUNCES << "\n";
    std::cout << "\t-Importance threshold: " << IMPORTANCE_THRESHOLD << "\n\n";
    
    std::cout << "Creating camera...\n";
    vec3 main_observer(-2, 0, 0);
    vec3 sub_observer(-1, 0, 0);
    Camera camera(main_observer, sub_observer);
    std::cout << "DONE!\n\n";

    std::cout << "Changing to secondary observer...\n";
    camera.toggleObserver();
    std::cout << "DONE!\n\n";

    std::cout << "Creating scene...\n";
    Scene scene;
    std::cout << "DONE!\n\n";

    std::cout << "Creating all materials...\n";
    Mirror mirror{};
    Light white_light{ WHITE, 25.0 };
    Light red_light{ RED, 25.0 };
    Light blue_light{ BLUE, 25.0 };
    DiffuseLambertian white_lambertian{ WHITE, 0.5 };
    DiffuseLambertian black_lambertian{ BLACK, 0.5 };
    DiffuseLambertian red_lambertian{ RED, 0.5 };
    DiffuseLambertian green_lambertian{ GREEN, 0.5 };
    DiffuseLambertian blue_lambertian{ BLUE, 0.5 };
    DiffuseLambertian cyan_lambertian{ CYAN, 0.5 };
    DiffuseLambertian teal_lambertian{ TEAL, 0.5 };
    DiffuseLambertian purple_lambertian{ PURPLE, 0.5 };
    DiffuseLambertian yellow_lambertian{ YELLOW, 0.5 };
    DiffuseLambertian pink_lambertian{ PINK, 0.5 };
    std::cout << "DONE!\n\n";

    std::cout << "Setting up room...\n";
    //Top
    const vec3 P1(0.0f, 6.0f, -5.0f); // = vec3(0.0f, 6.0f, -5.0f);
    const vec3 P2 = vec3(-3.0f, 0.0f, -5.0f);
    const vec3 P3 = vec3(0.0f, -6.0f, -5.0f);
    const vec3 P4 = vec3(10.0f, -6.0f, -5.0f);
    const vec3 P5 = vec3(13.0f, 0.0f, -5.0f);
    const vec3 P6 = vec3(10.0f, 6.0f, -5.0f);

    //Bottom
    const vec3 P7 = vec3(0.0f, 6.0f, 5.0f);
    const vec3 P8 = vec3(-3.0f, 0.0f, 5.0f);
    const vec3 P9 = vec3(0.0f, -6.0f, 5.0f);
    const vec3 P10 = vec3(10.0f, -6.0f, 5.0f);
    const vec3 P11 = vec3(13.0f, 0.0f, 5.0f);
    const vec3 P12 = vec3(10.0f, 6.0f, 5.0f);

    //Square light
    const vec3 P13 = vec3(6.0f, -1.0f, -4.9f);
    const vec3 P14 = vec3(5.0f, -3.0f, -4.9f);
    const vec3 P15 = vec3(5.0f, -1.0f, -4.9f);
    const vec3 P16 = vec3(6.0f, -3.0f, -4.9f);

    //Top
    Triangle triangle1 = Triangle(P1, P2, P3, &purple_lambertian);
    Triangle triangle2 = Triangle(P4, P5, P6, &purple_lambertian);
    Triangle triangle3 = Triangle(P1, P3, P6, &purple_lambertian);
    Triangle triangle4 = Triangle(P3, P4, P6, &purple_lambertian);

    //Bottom
    Triangle triangle5 = Triangle(P9, P8, P7, &pink_lambertian);
    Triangle triangle6 = Triangle(P12, P11, P10, &pink_lambertian);
    Triangle triangle7 = Triangle(P9, P7, P12, &pink_lambertian);
    Triangle triangle8 = Triangle(P9, P12, P10, &pink_lambertian);

    //Wall 1
    Triangle triangle9 = Triangle(P3, P9, P10, &red_lambertian);
    Triangle triangle10 = Triangle(P3, P10, P4, &red_lambertian);

    //Wall 2
    Triangle triangle11 = Triangle(P10, P11, P4, &blue_lambertian);
    Triangle triangle12 = Triangle(P11, P5, P4, &blue_lambertian);

    //Wall 3
    Triangle triangle13 = Triangle(P11, P12, P5, &green_lambertian);
    Triangle triangle14 = Triangle(P12, P6, P5, &green_lambertian);

    //Wall 4
    Triangle triangle15 = Triangle(P12, P7, P6, &cyan_lambertian);
    Triangle triangle16 = Triangle(P7, P1, P6, &cyan_lambertian);

    //Wall 5
    Triangle triangle17 = Triangle(P7, P8, P1, &white_lambertian);
    Triangle triangle18 = Triangle(P1, P8, P2, &white_lambertian);

    //Wall 6
    Triangle triangle19 = Triangle(P2, P8, P9, &white_lambertian);
    Triangle triangle20 = Triangle(P2, P9, P3, &white_lambertian);

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
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding mirror sphere...\n";
    Sphere s1{ vec3(10.0f, -1.5f, -0.5f), 1.5f, &mirror };
    scene.addObject(&s1);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding yellow sphere...\n";
    Sphere s2{ dvec3(8.0f, 2.5f, 0.65f), 1.0f, &yellow_lambertian };
    scene.addObject(&s2);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding mirror box...\n";
    Box b1 = Box(vec3(5.0f, 1.0f, 3.0f), 0.5f, 0.5f, 2.0f, &mirror);
    scene.addBox(&b1);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding white box...\n";
    Box b2 = Box(vec3(8.0f, 3.0f, 3.5f), 3.5f, 3.5f, 3.5f, &white_lambertian);
    scene.addBox(&b2);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding square area light...\n";
    Triangle al1 = Triangle(P14, P13, P15, &white_light);
    Triangle al2 = Triangle(P16, P13, P14, &white_light);
    scene.addAreaLight(&al1);
    scene.addAreaLight(&al2);
    std::cout << "DONE!\n";
    std::cout << "Number of area lights: " << scene.area_lights.size() << "\n\n";

    std::cout << "Rendering scene...\n";
    camera.render(scene);
    std::cout << "DONE!\n\n";

    std::cout << "Creating image...\n";

    //camera.dynamicRange();

    camera.createImage("../Renders/fix_bounces_1.bmp");
    std::cout << "DONE!\n\n";
    std::cout << "Exiting program...\n";

    return 0;
}
