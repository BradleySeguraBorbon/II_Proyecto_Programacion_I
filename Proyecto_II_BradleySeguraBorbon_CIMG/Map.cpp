#include "Map.h"

Map::Map() {
	map.assign("Resources/map.png");
	map.resize(800, 684);
	CImg<unsigned char>* addRouteImage = new CImg<unsigned char>("Resources/continue.png");
	addRouteImage->resize(addRouteImage->width() / 2, addRouteImage->height() / 2);
	addRouteButton = new Button(addRouteImage, 0, 0);
}

bool Map::isClicking(float mouseX, float mouseY, Button& buttonPressed) {
	return mouseX > buttonPressed.getX() and mouseX < buttonPressed.getX() + buttonPressed.getButtonImage()->width() and
		mouseY > buttonPressed.getY() and mouseY < buttonPressed.getButtonImage()->height();
}

void Map::displayMap() {
	const int windowWidth = 1280, windowHeight = 720;
	CImgDisplay window(windowWidth, windowHeight, "MAP");
	CImg<unsigned char> background(windowWidth, windowHeight, 1, 3, 255);

	const int x = (windowWidth - map.width()) / 2, y = (windowHeight - map.height()) / 2;
	background.draw_image(x, y, map);
	background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *addRouteButton->getButtonImage());
	window.display(background);

	cout << map.front() << endl;

	while (!window.is_closed()) {
		window.wait();
		if (isClicking(window.mouse_x(), window.mouse_y(), *addRouteButton) and window.button() & 1) {
			cout << "BUTTON PRESSED" << endl;
		}
	}
}