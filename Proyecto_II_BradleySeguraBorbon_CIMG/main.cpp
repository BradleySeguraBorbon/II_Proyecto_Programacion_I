#include <iostream>
#include "CImg.h"
#include "Route.h"
#include "Path.h"
#include "Vertice.h"

using namespace std;
using namespace cimg_library;

int main() {
	const int windowWidth = 1280, windowHeight = 720;
	CImgDisplay window(windowWidth, windowHeight, "MAP");
	CImg<unsigned char> background(windowWidth, windowHeight, 1, 3, 255);
	CImg<unsigned char> map("Resources/map.png");
	map.resize(800, 684);
	const int x = (windowWidth - map.width()) / 2, y = (windowHeight - map.height()) / 2;
	background.draw_image(x, y, map);
	window.display(background);

	while (!window.is_closed()) {
		window.wait();
	}
}