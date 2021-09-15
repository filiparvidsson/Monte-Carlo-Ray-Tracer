#include "Camera.h"

float constexpr DELTA = 0.0025f;

Camera::Camera()
{
	//Camera plane
	plane[0][0] = Vertex(0, -1, -1); //Left bottom corner
	plane[0][1] = Vertex(0, 1, -1); //Right bottom corner
	plane[1][0] = Vertex(0, -1, 1); //Left top corner
	plane[1][1] = Vertex(0, 1, 1); //Right top corner

	observer = Vertex(-2, 0, 0); // Default, should be able to switch to (-1,0,0)

	pixel_delt = DELTA;
}

void Camera::render() {

}

void Camera::createImage() {

	// Test render 
	/*FILE* out_img = fopen("../Renders/out_img.bmp", "w");
	
	for (int i = 0; i < RESOLUTION; ++i) {
		for (int j = 0; j < RESOLUTION; ++j) {
			fwrite(&i, 1, 1, out_img);
			fwrite(&j, 1, 1, out_img);
		}	
	}

	fclose(out_img);*/



}

void Camera::createImage2(Scene& scene)
{
	/*std::vector< double > charges = {1024.0, 2048.0};
	// R, G, B [0, 255]
	EasyBMP::RGBColor black(0, 0, 0);
	// sizeX, sizeY, FileName, BackgroundColor
	EasyBMP::Image img(800, 800, "sample.bmp", black);

	int final_color = 250;

	for (int y = 0; y < 800; ++y) {
		for (int x = 0; x < 800; ++x) {

			for (int i = 0; i < scene.getTriangles().size(); ++i) {
				
			}

				// PositionX, PisitionY, Color
				img.SetPixel(x, y, EasyBMP::RGBColor(final_color, 0, 0)); //Final color is an int
		}
	}
	img.Write();*/

	std::cout << "the scene has " << scene.getTriangles().size() << " Triangles, let's create an image";
}
