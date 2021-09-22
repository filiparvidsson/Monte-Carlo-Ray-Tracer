#include "Camera.h"
#include "EasyBMP.hpp"

double constexpr PIX_DELTA = 0.0025;

Camera::Camera(Vertex obs1, Vertex obs2)
	: obs1{obs1}, obs2{obs2}, main_obs{ true }
{
	//Camera plane
	plane[0][0] = Vertex(0, -1, -1); //Left bottom corner
	plane[0][1] = Vertex(0, 1, -1); //Right bottom corner
	plane[1][0] = Vertex(0, -1, 1); //Left top corner
	plane[1][1] = Vertex(0, 1, 1); //Right top corner
	pixels = new std::array<Pixel, RESOLUTION * RESOLUTION>();
	pixels->fill(Pixel{ ColorDbl(0.0, 0.0, 0.0) });
}

void Camera::render(Scene& scene) {

	vec3 p_start = Camera::main_obs ? obs1 : obs2;
	vec3 p_end;
	Ray ray;

	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {
			
			Pixel& p = getPixel(i, j);
			p_end = vec3(0.0, i*PIX_DELTA-(1.0-PIX_DELTA), j*PIX_DELTA-(1.0-PIX_DELTA));
			ray = Ray(p_start, p_end);

			// This part might need fixing to get the scene to show up
			for (Triangle& tri : scene.getTriangles()) {
				if (tri.rayIntersection(ray) > 0.0) {
					p.color = tri.getColor();
					break;
				}
			}
		}
	}
}

void Camera::createImage(const char* filepath) {

	EasyBMP::RGBColor rgb(0, 0, 0);
	EasyBMP::Image image(RESOLUTION, RESOLUTION, filepath, rgb);

	for (size_t i = 0; i < RESOLUTION; ++i) {
		for (size_t j = 0; j < RESOLUTION; ++j) {

			Pixel& p = getPixel(i, j);

			rgb = EasyBMP::RGBColor(static_cast<uint8_t>(p.color.x*255.99), static_cast<uint8_t>(p.color.y * 255.99), static_cast<uint8_t>(p.color.z * 255.99));
			image.SetPixel(i, j, rgb);
		}
	}
	image.Write();
}

Pixel& Camera::getPixel(size_t i, size_t j) {
	return (*pixels)[i * RESOLUTION + j];
}

//void Camera::createImage2(Scene& scene)
//{
//	/*std::vector< double > charges = {1024.0, 2048.0};
//	// R, G, B [0, 255]
//	EasyBMP::RGBColor black(0, 0, 0);
//	// sizeX, sizeY, FileName, BackgroundColor
//	EasyBMP::Image img(800, 800, "sample.bmp", black);
//
//	int final_color = 250;
//
//	for (int y = 0; y < 800; ++y) {
//		for (int x = 0; x < 800; ++x) {
//
//			for (int i = 0; i < scene.getTriangles().size(); ++i) {
//				
//			}
//
//				// PositionX, PisitionY, Color
//				img.SetPixel(x, y, EasyBMP::RGBColor(final_color, 0, 0)); //Final color is an int
//		}
//	}
//	img.Write();*/
//
//	std::cout << "the scene has " << scene.getTriangles().size() << " Triangles, let's create an image";
//}
