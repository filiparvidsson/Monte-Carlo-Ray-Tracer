#include "dependencies.h"


int main()
{
    std::cout << "Current settings: \n";
    std::cout << "- Picture resolution: " << RESOLUTION << " x " << RESOLUTION << " pixels\n";
    std::cout << "- Number of samples per pixel: " << N_SAMPLES_PIXEL << "\n";
    std::cout << "- Number of shadow rays: " << N_SHADOW_RAYS << "\n";
    std::cout << "- Number of bounces on diffuse surfaces: " << N_DIFFUSE_BOUNCES << "\n";
    std::cout << "- Importance threshold: " << IMPORTANCE_THRESHOLD << "\n";
    std::cout << "- Minimum absorption: " << MIN_DIFFUSE_ABSORPTION << "\n";
    std::cout << "- Maximum absorption: " << MAX_DIFFUSE_ABSORPTION << "\n";
    std::cout << "- Diffuse standard reflectance: " << DIFFUSE_REFLECTANCE << "\n";
    std::cout << "- Glass standard reflective index: " << GLASS_REFLECTIVE_INDEX << "\n";
    std::cout << "- Air standard reflective index: " << AIR_REFLECTIVE_INDEX << "\n";
    std::cout << "- Global color contribution: " << GLOBAL_COLOR_CONTRIBUTION << "\n";
    std::cout << "- Maximum ray depth: " << MAX_RAY_DEPTH << "\n";
    std::cout << "- Dropoff power: " << DROPOFF_POWER << "\n";
    std::cout << "\n";
    
    std::cout << "Creating camera...\n";
    vec3 main_observer{ -2, 0, 0 };
    vec3 sub_observer{ -1, 0, 0 };
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

    Light white_light{ WHITE, 10 };

    DiffuseLambertian white_lambertian{ WHITE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian dark_gray_lambertian{ DARK_GRAY, DIFFUSE_REFLECTANCE };
    DiffuseLambertian black_lambertian{ BLACK, DIFFUSE_REFLECTANCE };
    DiffuseLambertian red_lambertian{ RED, DIFFUSE_REFLECTANCE };
    DiffuseLambertian green_lambertian{ GREEN, DIFFUSE_REFLECTANCE };
    DiffuseLambertian blue_lambertian{ BLUE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian cyan_lambertian{ CYAN, DIFFUSE_REFLECTANCE };
    DiffuseLambertian teal_lambertian{ TEAL, DIFFUSE_REFLECTANCE };
    DiffuseLambertian purple_lambertian{ PURPLE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian dark_purple_lambertian{ DARK_PURPLE, DIFFUSE_REFLECTANCE };
    DiffuseLambertian yellow_lambertian{ YELLOW, DIFFUSE_REFLECTANCE };
    DiffuseLambertian pink_lambertian{ PINK, DIFFUSE_REFLECTANCE };

    Glass glass{ BLACK, GLASS_REFLECTIVE_INDEX };
    Glass light_blue_glass{ LIGHT_BLUE, GLASS_REFLECTIVE_INDEX };
    Glass purple_glass{ PURPLE, GLASS_REFLECTIVE_INDEX };
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
    const vec3 P1{ 0.0f, 6.0f, -5.0f };
    const vec3 P2{ -3.0f, 0.0f, -5.0f };
    const vec3 P3{ 0.0f, -6.0f, -5.0f };
    const vec3 P4{ 10.0f, -6.0f, -5.0f };
    const vec3 P5{ 13.0f, 0.0f, -5.0f };
    const vec3 P6{ 10.0f, 6.0f, -5.0f };

    //Bottom
    const vec3 P7{ 0.0f, 6.0f, 5.0f };
    const vec3 P8{ -3.0f, 0.0f, 5.0f };
    const vec3 P9{ 0.0f, -6.0f, 5.0f };
    const vec3 P10{ 10.0f, -6.0f, 5.0f };
    const vec3 P11{ 13.0f, 0.0f, 5.0f };
    const vec3 P12{ 10.0f, 6.0f, 5.0f };

    //Center light
    const vec3 P13{ 6.0f, 1.0f, -4.8f };
    const vec3 P14{ 5.0f, -1.0f, -4.8f };
    const vec3 P15{ 5.0f, 1.0f, -4.8f };
    const vec3 P16{ 6.0f, -1.0f, -4.8f };

    //Top
    Triangle triangle1{ P1, P2, P3, &white_lambertian };
    Triangle triangle2{ P4, P5, P6, &white_lambertian };
    Triangle triangle3{ P1, P3, P6, &white_lambertian };
    Triangle triangle4{ P3, P4, P6, &white_lambertian };

    //Bottom
    Triangle triangle5{ P9, P8, P7, &pink_lambertian };
    Triangle triangle6{ P12, P11, P10, &pink_lambertian };
    Triangle triangle7{ P9, P7, P12, &pink_lambertian };
    Triangle triangle8{ P9, P12, P10, &pink_lambertian };

    //Wall 1
    Triangle triangle9{ P3, P9, P10, &cyan_lambertian };
    Triangle triangle10{ P3, P10, P4, &cyan_lambertian };

    //Wall 2
    Triangle triangle11{ P10, P11, P4, &red_lambertian };
    Triangle triangle12{ P11, P5, P4, &red_lambertian };

    //Wall 3
    Triangle triangle13{ P11, P12, P5, &green_lambertian };
    Triangle triangle14{ P12, P6, P5, &green_lambertian };

    //Wall 4
    Triangle triangle15{ P12, P7, P6, &dark_purple_lambertian };
    Triangle triangle16{ P7, P1, P6, &dark_purple_lambertian };

    //Wall 5
    Triangle triangle17{ P7, P8, P1, &mirror };
    Triangle triangle18{ P1, P8, P2, &mirror };

    //Wall 6
    Triangle triangle19{ P2, P8, P9, &mirror };
    Triangle triangle20{ P2, P9, P3, &mirror };

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

    std::cout << "Adding black box...\n";
    Box b1 = Box(vec3(5.0f, 3.0f, 4.0f), 2.0f, 1.5f, 1.5f, &black_lambertian);
    scene.addBox(&b1);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding yellow box...\n";
    Box b2 = Box(vec3(5.0f, 0.0f, 4.0f), 2.0f, 1.5f, 1.5f, &yellow_lambertian);
    scene.addBox(&b2);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding white box...\n";
    Box b3 = Box(vec3(5.0f, -3.0f, 4.0f), 2.0f, 1.5f, 1.5f, &white_lambertian);
    scene.addBox(&b3);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding mirror sphere...\n";
    Sphere s1{ vec3(8.5f, 0.0f, -1.0f), 2.0f, &mirror };
    scene.addObject(&s1);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding glass sphere...\n";
    Sphere s2{ vec3(5.0f, 3.0f, 1.9f), 1.0f, &glass };
    scene.addObject(&s2);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding light blue glass sphere...\n";
    Sphere s3{ vec3(5.0f, 0.0f, 1.9f), 1.0f, &light_blue_glass };
    scene.addObject(&s3);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding purple glass sphere...\n";
    Sphere s4{ vec3(5.0f, -3.0f, 1.9f), 1.0f, &purple_glass };
    scene.addObject(&s4);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

    std::cout << "Adding white area light...\n";
    Triangle al1{ P14, P13, P15, &white_light };
    Triangle al2{ P16, P13, P14, &white_light };
    scene.addAreaLight(&al1);
    scene.addAreaLight(&al2);
    std::cout << "DONE!\n";
    std::cout << "Number of area lights: " << scene.area_lights.size() << "\n\n";

    std::cout << "Adding area light border...\n";
    const vec3 P17{ 5.0f, 1.0f, -4.8f };
    const vec3 P18{ 5.0f, 1.0f, -5.0f };
    const vec3 P19{ 5.0f, -1.0f, -5.0f };
    const vec3 P20{ 5.0f, -1.0f, -4.8f };
    const vec3 P21{ 6.0f, 1.0f, -4.8f };
    const vec3 P22{ 6.0f, 1.0f, -5.0f };
    const vec3 P23{ 6.0f, -1.0f, -5.0f };
    const vec3 P24{ 6.0f, -1.0f, -4.8f };

    Triangle triangle21{ P17, P18, P19, &black_lambertian };
    Triangle triangle22{ P17, P19, P20, &black_lambertian };
    Triangle triangle23{ P17, P21, P18, &black_lambertian };
    Triangle triangle24{ P18, P21, P22, &black_lambertian };
    Triangle triangle25{ P21, P23, P22, &black_lambertian };
    Triangle triangle26{ P21, P24, P23, &black_lambertian };
    Triangle triangle27{ P19, P23, P24, &black_lambertian };
    Triangle triangle28{ P19, P24, P20, &black_lambertian };

    scene.addObject(&triangle21);
    scene.addObject(&triangle22);
    scene.addObject(&triangle23);
    scene.addObject(&triangle24);
    scene.addObject(&triangle25);
    scene.addObject(&triangle26);
    scene.addObject(&triangle27);
    scene.addObject(&triangle28);
    std::cout << "DONE!\n";
    std::cout << "Number of objects: " << scene.objects.size() << "\n\n";

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
    std::cout << "Exiting program..." << std::endl;

    return 0;
}
