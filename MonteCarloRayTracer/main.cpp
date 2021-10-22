#include "dependencies.h"


int main()
{
    std::cout << "Current settings: \n";
    std::cout << "- Picture resolution: " << RESOLUTION << " x " << RESOLUTION << " pixels\n";
    std::cout << "- Number of samples per pixel: " << N_SAMPLES_PIXEL << "\n";
    std::cout << "- Number of shadow rays: " << N_SHADOW_RAYS << "\n";
    std::cout << "- Number of bounces on diffuse surfaces: " << N_DIFFUSE_BOUNCES << "\n";
    std::cout << "- Importance threshold: " << IMPORTANCE_THRESHOLD << "\n";
    std::cout << "- Minimum absorption: " << MIN_ABSORPTION << "\n";
    std::cout << "- Maximum absorption: " << MAX_ABSORPTION << "\n";
    std::cout << "- Diffuse standard reflectance: " << DIFFUSE_REFLECTANCE << "\n";
    std::cout << "- Glass standard reflective index: " << GLASS_REFLECTIVE_INDEX << "\n";
    std::cout << "- Air standard reflective index: " << AIR_REFLECTIVE_INDEX << "\n";
    std::cout << "- Global color contribution: " << GLOBAL_COLOR_CONTRIBUTION << "\n";
    std::cout << "- Maximum ray depth: " << MAX_RAY_DEPTH << "\n";
    std::cout << "- Dropoff power: " << DROPOFF_POWER << "\n";
    std::cout << "\n";
    
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

    Light white_light{ WHITE, 10.0 };
    Light light_blue_light{ BLUE, 7.5 };

    DiffuseLambertian white_lambertian{ WHITE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian black_lambertian{ BLACK, DIFFUSE_REFLECTANCE };
    DiffuseLambertian red_lambertian{ RED, DIFFUSE_REFLECTANCE };
    DiffuseLambertian green_lambertian{ GREEN, DIFFUSE_REFLECTANCE };
    DiffuseLambertian blue_lambertian{ BLUE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian cyan_lambertian{ CYAN, DIFFUSE_REFLECTANCE };
    DiffuseLambertian teal_lambertian{ TEAL, DIFFUSE_REFLECTANCE };
    DiffuseLambertian purple_lambertian{ PURPLE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian yellow_lambertian{ YELLOW, DIFFUSE_REFLECTANCE };
    DiffuseLambertian pink_lambertian{ PINK, DIFFUSE_REFLECTANCE };

    Glass glass{ BLACK, 2.0 };
    Glass green_glass{ GREEN, GLASS_REFLECTIVE_INDEX };
    Glass white_glass{ WHITE, GLASS_REFLECTIVE_INDEX };
    std::cout << "DONE!\n\n";

    std::cout << "Setting up room...\n";
    /*

      (1)--------(6)
      /            \
  (2)/              \(5)
     \    Top       /
      \            /
      (3)--------(4)

      (7)--------(12)
      /            \
  (8)/              \(11)
     \    Bottom    /
      \            /
      (9)--------(10)
  */

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

    //Center light
    const vec3 P13 = vec3(6.0f, 1.0f, -4.8f);
    const vec3 P14 = vec3(5.0f, -1.0f, -4.8f);
    const vec3 P15 = vec3(5.0f, 1.0f, -4.8f);
    const vec3 P16 = vec3(6.0f, -1.0f, -4.8f);

    //Center lamp border
    const vec3 P17 = vec3(5.0f, 1.0f, -4.8f);
    const vec3 P18 = vec3(5.0f, 1.0f, -5.0f);
    const vec3 P19 = vec3(5.0f, -1.0f, -5.0f);
    const vec3 P20 = vec3(5.0f, -1.0f, -4.8f);
    const vec3 P21 = vec3(6.0f, 1.0f, -4.8f);
    const vec3 P22 = vec3(6.0f, 1.0f, -5.0f);
    const vec3 P23 = vec3(6.0f, -1.0f, -5.0f);
    const vec3 P24 = vec3(6.0f, -1.0f, -4.8f);

    //Left light
    const vec3 P25 = vec3(6.0f, -5.8f, -0.5f);
    const vec3 P26 = vec3(7.0f, -5.8f, -0.5f);
    const vec3 P27 = vec3(6.0f, -5.8f, 0.5f);
    const vec3 P28 = vec3(7.0f, -5.8f, 0.5f);

    //Left light border
    const vec3 P29 = vec3(6.0f, -5.8f, -0.5f);
    const vec3 P30 = vec3(6.0f, -5.8f, 0.5f);
    const vec3 P31 = vec3(6.0f, -6.0f, -0.5f);
    const vec3 P32 = vec3(6.0f, -6.0f, 0.5f);
    const vec3 P33 = vec3(7.0f, -5.8f, -0.5f);
    const vec3 P34 = vec3(7.0f, -5.8f, 0.5f);
    const vec3 P35 = vec3(7.0f, -6.0f, -0.5f);
    const vec3 P36 = vec3(7.0f, -6.0f, 0.5f);

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

    //Center light border
    Triangle triangle21 = Triangle(P17, P18, P19, &black_lambertian);
    Triangle triangle22 = Triangle(P17, P19, P20, &black_lambertian);
    Triangle triangle23 = Triangle(P17, P21, P18, &black_lambertian);
    Triangle triangle24 = Triangle(P18, P21, P22, &black_lambertian);
    Triangle triangle25 = Triangle(P21, P23, P22, &black_lambertian);
    Triangle triangle26 = Triangle(P21, P24, P23, &black_lambertian);
    Triangle triangle27 = Triangle(P19, P23, P24, &black_lambertian);
    Triangle triangle28 = Triangle(P19, P24, P20, &black_lambertian);

    //Left light border
    Triangle triangle29 = Triangle(P29, P31, P30, &black_lambertian);
    Triangle triangle30 = Triangle(P30, P31, P32, &black_lambertian);
    Triangle triangle31 = Triangle(P30, P32, P36, &black_lambertian);
    Triangle triangle32 = Triangle(P30, P36, P34, &black_lambertian);
    Triangle triangle33 = Triangle(P34, P36, P35, &black_lambertian);
    Triangle triangle34 = Triangle(P33, P34, P35, &black_lambertian);
    Triangle triangle35 = Triangle(P29, P33, P35, &black_lambertian);
    Triangle triangle36 = Triangle(P29, P35, P31, &black_lambertian);

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
    scene.addObject(&triangle21);
    scene.addObject(&triangle22);
    scene.addObject(&triangle23);
    scene.addObject(&triangle24);
    scene.addObject(&triangle25);
    scene.addObject(&triangle26);
    scene.addObject(&triangle27);
    scene.addObject(&triangle28);
    scene.addObject(&triangle29);
    scene.addObject(&triangle30);
    scene.addObject(&triangle31);
    scene.addObject(&triangle32);
    scene.addObject(&triangle33);
    scene.addObject(&triangle34);
    scene.addObject(&triangle35);
    scene.addObject(&triangle36);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding mirror sphere...\n";
    Sphere s1{ vec3(9.5f, -1.25f, -0.5f), 1.5f, &mirror };
    scene.addObject(&s1);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding yellow sphere...\n";
    Sphere s2{ vec3(6.0f, 2.5f, 0.65f), 1.0f, &yellow_lambertian };
    scene.addObject(&s2);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding white box...\n";
    Box b3 = Box(vec3(6.0f, 3.0f, 3.5f), 3.5f, 3.5f, 3.5f, &white_lambertian);
    scene.addBox(&b3);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding glass sphere...\n";
    Sphere s3{ dvec3(8.0f, 3.0f, -2.5f), 1.75f, &glass };
    scene.addObject(&s3);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding green glass box...\n";
    Box b2 = Box(vec3(6.0f, -3.0f, 2.0f), 2.0f, 2.0f, 1.5f, &green_glass);
    scene.addBox(&b2);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding center white area light...\n";
    Triangle al1 = Triangle(P14, P13, P15, &white_light);
    Triangle al2 = Triangle(P16, P13, P14, &white_light);
    scene.addAreaLight(&al1);
    scene.addAreaLight(&al2);
    std::cout << "DONE!\n";
    std::cout << "Number of area lights: " << scene.area_lights.size() << "\n\n";

    std::cout << "Adding left blue area light...\n";
    Triangle al3 = Triangle(P25, P27, P26, &light_blue_light);
    Triangle al4 = Triangle(P26, P27, P28, &light_blue_light);
    scene.addAreaLight(&al3);
    scene.addAreaLight(&al4);
    std::cout << "DONE!\n";
    std::cout << "Number of area lights: " << scene.area_lights.size() << "\n\n";

    std::cout << "Rendering scene...\n";
    auto start_time{ std::chrono::system_clock::now() };

    #ifdef NOTHREAD
    std::cout << "Using 1 CPU thread..."
    camera.render(scene, 0, RESOLUTION, 0, RESOLUTION);
    #else
    std::cout << "Using 4 CPU threads...\n";
    std::thread t1(&Camera::render, std::ref(camera), std::ref(scene), 0, RESOLUTION / 2, 0, RESOLUTION / 2);
    std::thread t2(&Camera::render, std::ref(camera), std::ref(scene), RESOLUTION / 2, RESOLUTION, 0, RESOLUTION / 2);
    std::thread t3(&Camera::render, std::ref(camera), std::ref(scene), 0, RESOLUTION / 2, RESOLUTION / 2, RESOLUTION);
    std::thread t4(&Camera::render, std::ref(camera), std::ref(scene), RESOLUTION / 2, RESOLUTION, RESOLUTION / 2, RESOLUTION);
    t1.join(); t2.join(); t3.join(); t4.join();
    #endif

    auto end_time{ std::chrono::system_clock::now() };
    std::cout << "DONE!\n";
    auto seconds{ std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() };
    auto minutes = std::floor(seconds / 60);
    seconds = seconds % 60;
    std::cout << "Rendering took " << minutes << " minutes and " << seconds << " seconds.\n\n";

    std::cout << "Creating image...\n";
    std::ostringstream file_path;
    file_path << "../Renders/SPP-" << N_SAMPLES_PIXEL << "_SR-" << N_SHADOW_RAYS << "_DB-" << N_DIFFUSE_BOUNCES << "_DR-" << DIFFUSE_REFLECTANCE
                                   << "_GCC-" << GLOBAL_COLOR_CONTRIBUTION << "_DP-" << DROPOFF_POWER << "_T-" << minutes << "min" << seconds << "sec.bmp";
    const std::string s = file_path.str();
    camera.createImage(s.c_str());
    std::cout << "DONE!\n\n";
    std::cout << "Exiting program...\n";

    return 0;
}
