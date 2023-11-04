#include "Map.h"

unsigned char red[3] = { 255, 1, 1 }, blue[3] = { 1, 1, 255 }, green[3] = { 1, 255, 1 };

Map::Map() {
	map.assign("Resources/forza.jpg");
	map.resize(1080, 607); //950, 812
	CImg<unsigned char>* addRouteImage = new CImg<unsigned char>("Resources/AgregarRuta1.png");
	CImg<unsigned char>* finishRouteImage = new CImg<unsigned char>("Resources/FinalizarRuta.png");
	CImg<unsigned char>* deleteRouteImage = new CImg<unsigned char>("Resources/EliminarRuta.png");
	CImg<unsigned char>* saveRoutesImage = new CImg<unsigned char>("Resources/GuardarRutas1.png");
	CImg<unsigned char>* loadRouteImage = new CImg<unsigned char>("Resources/CargarRutas1.png");
	CImg<unsigned char>* showRouteImage = new CImg<unsigned char>("Resources/MostrarRuta.png");
	CImg<unsigned char>* hideRouteImage = new CImg<unsigned char>("Resources/OcultarRuta.png");
	CImg<unsigned char>* colorsImage = new CImg<unsigned char>("Resources/colors.jpg");
	CImg<unsigned char>* cancelSelectionImage = new CImg<unsigned char>("Resources/CancelarSeleccion.png");
	CImg<unsigned char>* deleteVerticeImage = new CImg<unsigned char>("Resources/EliminarVertice.png");
	colorsImage->resize(804, 100);
	addRouteButton = new Button(addRouteImage, 32, 100, true);
	finishRouteButton = new Button(finishRouteImage, 32, 100, false);
	deleteRouteButton = new Button(deleteRouteImage, 32, 100, false);
	saveRoutesButton = new Button(saveRoutesImage, 32, 400, true);
	loadRouteButton = new Button(loadRouteImage, 32, 250, true);
	showRouteButton = new Button(showRouteImage, 32, 250, false);
	hideRouteButton = new Button(hideRouteImage, 32, 250, false);
	cancelSelectionButton = new Button(cancelSelectionImage, 32, 400, false);
	deleteVerticeButton = new Button(deleteVerticeImage, 32, 100, false);
	colorsButton = new Button(colorsImage, 594, 670, true);

	addingRoute = editingRoute = false;

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

unsigned char* Map::selectColor(CImgDisplay& window) {
	unsigned char* colors[7] = { red, yellow, cian, orange, purple, pink, blue };
	float blockSize = colorsButton->getButtonImage()->width() / 7.0;
	int i = 1;
	while (true) {
		float mouseX = window.mouse_x(), mouseY = window.mouse_y();
		if (window.button() & 1 and colorsButton->contains(mouseX, mouseY)) {
			cout << "Pressed colorsButton" << endl;
			while (i <= 7) {
				if (mouseX < colorsButton->getX() + blockSize * i) {
					cout << "Returned a unsigned char ptr" << endl;
					return colors[i - 1];
				}
				i++;
			}
		}
	}
}

bool Map::isRouteSelected(float x, float y) {
	Node<Route>* currentRoute = routes.getHeadNode();
	while (currentRoute) {
		if (currentRoute->data->contains(x, y)) {
			cout << currentRoute->data->getName() << " IS SELECTED" << endl;
			return true;
		}
		currentRoute = currentRoute->next;
	}
	return false;
}

Route* Map::getSelectedRoute() {
	Node<Route>* currentRoute = routes.getHeadNode();
	while (currentRoute) {
		if (currentRoute->data->selected()) {
			return currentRoute->data;
		}
	}
}

void Map::displayMap() {
	const int windowWidth = 1920, windowHeight = 1080;
	CImgDisplay window(windowWidth, windowHeight, "MAP");
	CImg<unsigned char> background(windowWidth, windowHeight, 1, 3, 255);
	CImg<unsigned char> backgroundImage("Resources/background.jpg");
	backgroundImage.resize(1540, 790);

	const int mapX = (1540 - map.width()), mapY = 0;

	float X, Y;
	addingRoute = editingRoute = false;
	List<Button> buttons;
	buttons.pushBack(addRouteButton);
	buttons.pushBack(finishRouteButton);
	buttons.pushBack(deleteRouteButton);
	buttons.pushBack(saveRoutesButton);
	buttons.pushBack(loadRouteButton);
	buttons.pushBack(showRouteButton);
	buttons.pushBack(hideRouteButton);
	buttons.pushBack(cancelSelectionButton);
	buttons.pushBack(deleteVerticeButton);

	string name;
	unsigned char* color = nullptr;
	Route* selectedRoute = nullptr; 
	bool firstVertice;

	while (!window.is_closed()) {
		window.wait();
		if (window.button() & 1) cout << window.mouse_x() << ", " << window.mouse_y() << endl;
		if ((addRouteButton->isAvailable() || finishRouteButton->isAvailable()) and addRouteButton->contains(window.mouse_x(), window.mouse_y()) and window.button() & 1) {
			cout << "BUTTON PRESSED" << endl;
			if (finishRouteButton->isAvailable()) {
				addRouteButton->setAvailability(true);
				finishRouteButton->setAvailability(false);
				saveRoutesButton->setAvailability(true);
				loadRouteButton->setAvailability(true);
			}
			else {
				addRouteButton->setAvailability(false);
				finishRouteButton->setAvailability(true);
				saveRoutesButton->setAvailability(false);
				loadRouteButton->setAvailability(false);
				HWND consoleWindow = GetConsoleWindow();
				ShowWindow(consoleWindow, SW_MAXIMIZE);
				cout << "Ingrese el nombre de la nueva ruta: ";
				cin >> name;
				ShowWindow(consoleWindow, SW_MINIMIZE);
				color = selectColor(window);
				Route* newRoute = new Route(name, color);
				routes.pushBack(newRoute);
				newRoute = nullptr;
			}
		}
		else if (saveRoutesButton->isAvailable() and window.button() & 1 and saveRoutesButton->contains(window.mouse_x(), window.mouse_y())) {
			saveRoutes();
		}
		else if (loadRouteButton->isAvailable() and window.button() & 1 and loadRouteButton->contains(window.mouse_x(), window.mouse_y())) {
			string routeName;
			cout << "Enter the route name: ";
			cin >> routeName;
			Route* newRoute = new Route();
			newRoute->loadRoute(routeName);
			routes.pushBack(newRoute);
		}
		else if (deleteRouteButton->isAvailable() and window.button() & 1 and deleteRouteButton->contains(window.mouse_x(), window.mouse_y())) {
			selectedRoute = getSelectedRoute();
			routes.deleteElement(selectedRoute);
			addRouteButton->setAvailability(true);
			loadRouteButton->setAvailability(true);
			saveRoutesButton->setAvailability(true);
			deleteRouteButton->setAvailability(false);
			hideRouteButton->setAvailability(false);
			cancelSelectionButton->setAvailability(false);
		}
		else if (cancelSelectionButton->isAvailable() and window.button() & 1 and cancelSelectionButton->contains(window.mouse_x(), window.mouse_y())) {
			addRouteButton->setAvailability(true);
			loadRouteButton->setAvailability(true);
			saveRoutesButton->setAvailability(true);
			deleteRouteButton->setAvailability(false);
			hideRouteButton->setAvailability(false);
			cancelSelectionButton->setAvailability(false);
			selectedRoute->setSelection(false);
			selectedRoute = nullptr;
		}
		else if (window.button() & 1 and finishRouteButton->isAvailable() and imageContains(mapX, mapY, map, window.mouse_x(), window.mouse_y())) {
			X = window.mouse_x();
			Y = window.mouse_y();
			routes.getLastElement()->addVertice(X, Y);
		}
		else if (window.button() & 1 and isRouteSelected(window.mouse_x(), window.mouse_y())) {
			addRouteButton->setAvailability(false);
			loadRouteButton->setAvailability(false);
			saveRoutesButton->setAvailability(false);
			deleteRouteButton->setAvailability(true);
			hideRouteButton->setAvailability(true);
			cancelSelectionButton->setAvailability(true);
			selectedRoute = getSelectedRoute();
		}
		else if (window.is_keyT()) {
			routes.toString();
		}
		background.draw_image(backgroundImage);
		background.draw_image(mapX, mapY, map);
		drawRoutes(background);
		Node<Button>* currentButton= buttons.getHeadNode();
		while (currentButton) {
			if (currentButton->data->isAvailable())
				background.draw_image(currentButton->data->getX(), currentButton->data->getY(), *currentButton->data->getButtonImage());
			currentButton = currentButton->next;
		}
		background.draw_image(colorsButton->getX(), colorsButton->getY(), *colorsButton->getButtonImage());
		window.display(background);
	}
}