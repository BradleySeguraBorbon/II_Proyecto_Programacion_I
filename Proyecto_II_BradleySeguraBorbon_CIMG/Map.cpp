#include "Map.h"

unsigned char red[3] = { 255, 1, 1 }, blue[3] = { 1, 1, 255 }, green[3] = { 1, 255, 1 };

Map::Map() {
	map.assign("Resources/forza.jpg");
	map.resize(1080, 607); //950, 812
	CImg<unsigned char>* addRouteImage = new CImg<unsigned char>("Resources/AgregarRuta.png");
	CImg<unsigned char>* finishRouteImage = new CImg<unsigned char>("Resources/FinalizarRuta.png");
	CImg<unsigned char>* deleteRouteImage = new CImg<unsigned char>("Resources/EliminarRuta.png");
	CImg<unsigned char>* saveRoutesImage = new CImg<unsigned char>("Resources/GuardarRutas.png");
	CImg<unsigned char>* loadRouteImage = new CImg<unsigned char>("Resources/CargarRutas.png");
	CImg<unsigned char>* showRouteImage = new CImg<unsigned char>("Resources/MostrarRuta.png");
	CImg<unsigned char>* hideRouteImage = new CImg<unsigned char>("Resources/OcultarRuta.png");
	CImg<unsigned char>* colorsImage = new CImg<unsigned char>("Resources/colors.jpg");
	colorsImage->resize(804, 100);
	addRouteButton = new Button(addRouteImage, 30, 100);
	finishRouteButton = new Button(finishRouteImage, 0, 200);
	deleteRouteButton = new Button(deleteRouteImage, 0, 400);
	saveRoutesButton = new Button(saveRoutesImage, 30, 400);
	loadRouteButton = new Button(loadRouteImage, 30, 250);
	showRouteButton = new Button(showRouteImage, 0, 400);
	hideRouteButton = new Button(hideRouteImage, 0, 600);
	colorsButton = new Button(colorsImage, 594, 670);

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
	CImg<unsigned char> background(windowWidth, windowHeight, 1, 3, 255); //windowWidth, windowHeight, 1, 3, 255
	CImg<unsigned char> backgroundImage("Resources/background.jpg");
	backgroundImage.resize(1540, 790);

	const int mapX = (1540 - map.width()), mapY = 0; //(790 - map.height());

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
		else if (window.button() & 1 and saveRoutesButton->contains(window.mouse_x(), window.mouse_y())) {
			saveRoutes();
		}
		else if (window.button() & 1 and loadRouteButton->contains(window.mouse_x(), window.mouse_y())) {
			string routeName;
			cout << "Enter the route name: ";
			cin >> routeName;
			Route* newRoute = new Route(name, "red");
			newRoute->loadRoute(routeName);
			routes.pushBack(newRoute);
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
		background.draw_image(backgroundImage);
		background.draw_image(mapX, mapY, map);
		drawRoutes(background);
		if(addingRoute)
			background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *finishRouteButton->getButtonImage());
		else
			background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *addRouteButton->getButtonImage());
		background.draw_image(saveRoutesButton->getX(), saveRoutesButton->getY(), *saveRoutesButton->getButtonImage());
		background.draw_image(loadRouteButton->getX(), loadRouteButton->getY(), *loadRouteButton->getButtonImage());
		background.draw_image(colorsButton->getX(), colorsButton->getY(), *colorsButton->getButtonImage());
		background.draw_circle(colorsButton->getX(), colorsButton->getY(), 0.5, red);
		background.draw_circle(colorsButton->getX(), colorsButton->getY() + colorsButton->getButtonImage()->height(), 0.5, red);
		background.draw_circle(colorsButton->getX() + colorsButton->getButtonImage()->width(), colorsButton->getY(), 0.5, red);
		background.draw_circle(colorsButton->getX() + colorsButton->getButtonImage()->width(), colorsButton->getY() + colorsButton->getButtonImage()->height(), 0.5, red);
		window.display(background);
	}
}