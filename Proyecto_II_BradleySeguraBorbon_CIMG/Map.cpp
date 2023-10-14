#include "Map.h"

Map::Map() {
	map.assign("Resources/map.png");
	map.resize(800, 684);
}

void isClicking(float mouseX, float mouseY, CImg<unsigned char>& object) {
	return mouseX > 
}

void Map::displayMap() {
	const int windowWidth = 1280, windowHeight = 720;
	CImgDisplay window(windowWidth, windowHeight, "MAP");
	CImg<unsigned char> background(windowWidth, windowHeight, 1, 3, 255);

	const int x = (windowWidth - map.width()) / 2, y = (windowHeight - map.height()) / 2;
	background.draw_image(x, y, map);
	window.display(background);

	cout << map.front() << endl;

	while (!window.is_closed()) {
		window.wait();
	}
}