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
	colorsButton = new Button(colorsImage, 594, 670, false);

	addingRoute = editingRoute = false;
	selectedRoute = nullptr;

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

unsigned char* Map::selectColor(CImgDisplay& window, CImg<unsigned char>& background) {
	unsigned char* colors[7] = { red, yellow, cian, orange, purple, pink, blue };
	float blockSize = colorsButton->getButtonImage()->width() / 7.0;
	int i = 1;
	background.draw_image(colorsButton->getX(), colorsButton->getY(), *colorsButton->getButtonImage());
	window.display(background);
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
			if(!selectedRoute)
				currentRoute->data->setSelection(true);
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
		currentRoute = currentRoute->next;
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
	bool firstVertice;

	while (!window.is_closed()) {
		window.wait();
		//if (window.button() & 1) cout << window.mouse_x() << ", " << window.mouse_y() << endl;
		if ((addRouteButton->isAvailable() || finishRouteButton->isAvailable()) and addRouteButton->contains(window.mouse_x(), window.mouse_y()) and window.button() & 1) {
			cout << "BUTTON PRESSED" << endl;
			if (finishRouteButton->isAvailable()) {
				cout << "-- FINISH ROUTE BUTTON PRESSED --" << endl;
				addRouteButton->setAvailability(true);
				finishRouteButton->setAvailability(false);
				saveRoutesButton->setAvailability(true);
				loadRouteButton->setAvailability(true);
			}
			else {
				cout << "-- ADD ROUTE BUTTON PRESSED --" << endl;
				addRouteButton->setAvailability(false);
				finishRouteButton->setAvailability(true);
				saveRoutesButton->setAvailability(false);
				loadRouteButton->setAvailability(false);
				/*HWND consoleWindow = GetConsoleWindow();
				ShowWindow(consoleWindow, SW_MAXIMIZE);*/
				cout << "Ingrese el nombre de la nueva ruta: ";
				cin >> name;
				//ShowWindow(consoleWindow, SW_MINIMIZE);
				color = selectColor(window, background);
				Route* newRoute = new Route(name, color);
				routes.pushBack(newRoute);
				newRoute = nullptr;
			}
		}
		else if (saveRoutesButton->isAvailable() and window.button() & 1 and saveRoutesButton->contains(window.mouse_x(), window.mouse_y())) {
			cout << "-- SAVE ROUTES BUTTON PRESSED --" << endl;
			saveRoutes();
		}
		else if (loadRouteButton->isAvailable() and window.button() & 1 and loadRouteButton->contains(window.mouse_x(), window.mouse_y())) {
			cout << "-- LOAD ROUTE BUTTON PRESSED --" << endl;
			string routeName;
			cout << "Enter the route name: ";
			cin >> routeName;
			Route* newRoute = new Route();
			newRoute->loadRoute(routeName);
			routes.pushBack(newRoute);
		}
		else if (deleteRouteButton->isAvailable() and window.button() & 1 and deleteRouteButton->contains(window.mouse_x(), window.mouse_y())) {
			cout << "-- DELETE ROUTE BUTTON PRESSED --" << endl;
			selectedRoute = getSelectedRoute();
			routes.deleteElement(selectedRoute);
			addRouteButton->setAvailability(true);
			loadRouteButton->setAvailability(true);
			saveRoutesButton->setAvailability(true);
			deleteRouteButton->setAvailability(false);
			hideRouteButton->setAvailability(false);
			cancelSelectionButton->setAvailability(false);
			selectedRoute = nullptr;
		}
		else if (cancelSelectionButton->isAvailable() and cancelSelectionButton->contains(window.mouse_x(), window.mouse_y()) and window.button() & 1) {
			cout << "-- CANCEL SELECTION BUTTON PRESSED --" << endl;
			if (selectedRoute->getSelectedVertice()) {
				deleteVerticeButton->setAvailability(false);
				deleteRouteButton->setAvailability(true);
				hideRouteButton->setAvailability(true);
				cancelSelectionButton->setAvailability(true);
				selectedRoute->setSelectedVertice(nullptr);
			}
			else {
				addRouteButton->setAvailability(true);
				loadRouteButton->setAvailability(true);
				saveRoutesButton->setAvailability(true);
				deleteRouteButton->setAvailability(false);
				hideRouteButton->setAvailability(false);
				showRouteButton->setAvailability(false);
				cancelSelectionButton->setAvailability(false);
				selectedRoute->setSelection(false);
				selectedRoute = nullptr;
			}
		}
		else if ((showRouteButton->isAvailable() || hideRouteButton->isAvailable()) and showRouteButton->contains(window.mouse_x(), window.mouse_y()) and window.button() & 1) {
			if (selectedRoute->isShowing()) {
				cout << "-- HIDE ROUTE BUTTON PRESSED --" << endl;
				selectedRoute->setShow(false);
				hideRouteButton->setAvailability(false);
				showRouteButton->setAvailability(true);
			}
			else {
				cout << "-- SHOW ROUTE BUTTON PRESSED --" << endl;
				selectedRoute->setShow(true);
				hideRouteButton->setAvailability(true);
				showRouteButton->setAvailability(false);
			}
		}
		else if (deleteVerticeButton->isAvailable() and deleteVerticeButton->contains(window.mouse_x(), window.mouse_y()) and window.button() & 1) {
			cout << "-- DELETE VERTICE BUTTON PRESSED --" << endl;
			selectedRoute->deleteSelectedVertice();
			deleteVerticeButton->setAvailability(false);
			deleteRouteButton->setAvailability(true);
			hideRouteButton->setAvailability(true);
			cancelSelectionButton->setAvailability(true);
		}
		else if (window.button() & 1 and finishRouteButton->isAvailable() and imageContains(mapX, mapY, map, window.mouse_x(), window.mouse_y())) {
			X = window.mouse_x();
			Y = window.mouse_y();
			routes.getLastElement()->addVertice(X, Y);
		}
		else if (window.button() & 1 and isRouteSelected(window.mouse_x(), window.mouse_y())) {
			selectedRoute = getSelectedRoute();
			if (selectedRoute) cout << selectedRoute->getName() << "IS THE ROUTE SELECTED" << endl;
			else cout << "No route selected" << endl;
			addRouteButton->setAvailability(false);
			loadRouteButton->setAvailability(false);
			saveRoutesButton->setAvailability(false);
			cancelSelectionButton->setAvailability(true);

			if (selectedRoute->getSelectedVertice()) {
				deleteVerticeButton->setAvailability(true);
				deleteRouteButton->setAvailability(false);
				hideRouteButton->setAvailability(false); showRouteButton->setAvailability(false);
			}
			else {
				deleteRouteButton->setAvailability(true);
				deleteVerticeButton->setAvailability(false);
				selectedRoute->isShowing() ? hideRouteButton->setAvailability(true) : showRouteButton->setAvailability(true);
			}
		}
		else if (window.is_keyT()) {
			cout << endl << endl << "    ----   ROUTES LIST   ----    " << endl << endl;
			routes.toString();
			cout << endl << endl << " - ROUTES QUANTITY - : " << routes.getSize() << endl << endl;
		}
		//Draw Section
		background.draw_image(backgroundImage);
		background.draw_image(mapX, mapY, map);
		drawRoutes(background);
		if (selectedRoute) {
			background.draw_text(32, 680, "SELECTED ROUTE", red, 1.0, 80);
			background.draw_text(32, 700, selectedRoute->getName().c_str(), red, 1.0, 80);
		}
		Node<Button>* currentButton= buttons.getHeadNode();
		while (currentButton) {
			if (currentButton->data->isAvailable())
				background.draw_image(currentButton->data->getX(), currentButton->data->getY(), *currentButton->data->getButtonImage());
			currentButton = currentButton->next;
		}
		window.display(background);
	}
}