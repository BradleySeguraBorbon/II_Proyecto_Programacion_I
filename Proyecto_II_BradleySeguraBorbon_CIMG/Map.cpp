#include "Map.h"

Map::Map() {
	map.assign("Resources/map.png");
	map.resize(950, 812);
	CImg<unsigned char>* addRouteImage = new CImg<unsigned char>("Resources/AgregarRuta.png");
	CImg<unsigned char>* finishRouteImage = new CImg<unsigned char>("Resources/FinalizarRuta.png");
	addRouteButton = new Button(addRouteImage, 0, 400);
	finishRouteButton = new Button(finishRouteImage, 0, 400);
}

bool Map::isClicking(float mouseX, float mouseY, Button& buttonPressed) {
	return mouseX > buttonPressed.getX() and mouseX < buttonPressed.getX() + buttonPressed.getButtonImage()->width() and
		mouseY > buttonPressed.getY() and mouseY < buttonPressed.getButtonImage()->height();
}

bool Map::imageContains(float imageX, float imageY, CImg<unsigned char>& image, float mouseX, float mouseY) {
	return mouseX > imageX and mouseX < imageX + image.width() and mouseY > imageY and mouseY < imageY + image.width();
}

void Map::drawRoutes(CImg<unsigned char>& window) {
	int position = 0;
	Node<Route>* currentRoute = routes.getHeadNode();
	while (currentRoute) {
		currentRoute->data->draw(window);
		currentRoute = currentRoute->next;
	}
}

void Map::saveRoutes() {
	Node<Route>* currentNode = routes.getHeadNode();
	while (currentNode) {
		currentNode->data->saveRoute();
		currentNode = currentNode->next;
	}
}

void Map::displayMap() {
	const int windowWidth = 1920, windowHeight = 1080;
	CImgDisplay window(windowWidth, windowHeight, "MAP");
	CImg<unsigned char> background(windowWidth, windowHeight, 1, 3, 255);

	const int mapX = (1540 - map.width()) / 2, mapY = (790 - map.height()) / 2;

	float X, Y;
	bool addingRoute = false;
	Vertice* firstVertice = nullptr;
	Vertice* lastVertice = nullptr;

	string name, color;

	while (!window.is_closed()) {
		window.wait();
		if (window.button() & 1) cout << window.mouse_x() << ", " << window.mouse_y() << endl;
		if (addRouteButton->contains(window.mouse_x(), window.mouse_y()) and window.button() & 1) {
			cout << "BUTTON PRESSED" << endl;
			if (addingRoute) {
				addingRoute = false;
				firstVertice = nullptr;
			}
			else {
				addingRoute = true;
				cout << "Ingrese el nombre de la nueva ruta: ";
				cin >> name;
			}
		}
		else if (window.button() & 1 and addingRoute and imageContains(mapX, mapY, map, window.mouse_x(), window.mouse_y())) {
			if (firstVertice) {
				X = window.mouse_x();
				Y = window.mouse_y();
				lastVertice = new Vertice(X, Y);
				Path* newPath = new Path(firstVertice, lastVertice);
				routes.getLastElement()->addPath(newPath);
				firstVertice = lastVertice;
			}
			else {
				X = window.mouse_x();
				Y = window.mouse_y();
				Route* newRoute = new Route(name, "red");
				routes.pushBack(newRoute);
				firstVertice = new Vertice(X, Y);
			}
		}
		background.draw_image(mapX, mapY, map);
		drawRoutes(background);
		if(addingRoute)
			background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *finishRouteButton->getButtonImage());
		else
			background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *addRouteButton->getButtonImage());
		window.display(background);
	}
}