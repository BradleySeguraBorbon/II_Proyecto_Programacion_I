#pragma once
#include <iostream>
#include "Route.h"
#include "List.h"
#include "CImg.h"
#include "Button.h"
#include "Vertice.h"
#include <string>
#include <windows.h>

using namespace std;
using namespace cimg_library;


class Map {
	List<Route> routes;
	CImg<unsigned char> map;
	Button* addRouteButton;
	Button* finishRouteButton;
	Button* deleteRouteButton;
	Button* saveRoutesButton;
	Button* loadRouteButton;
	Button* showRouteButton;
	Button* hideRouteButton;
	Button* cancelSelectionButton;
	Button* deleteVerticeButton;
	Button* colorsButton;
	bool addingRoute, editingRoute;

	unsigned char red[3] = { 255, 1, 1 }, blue[3] = { 1, 1, 255 }, green[3] = { 1, 255, 1 }, yellow[3] = { 255, 255, 0 }, cian[3] = { 0, 255, 255 },
		orange[3] = { 255, 60, 0 }, purple[3] = { 204, 0, 204 }, pink[3] = { 255, 51, 255 };

public:
	Map();
	~Map() {}
	void displayMap();
	bool imageContains(float imageX, float imageY, CImg<unsigned char>&, float mouseX, float mouseY);
	bool isClicking(float mouseX, float mouseY, Button& buttonPressed);
	void drawRoutes(CImg<unsigned char>& window);
	void saveRoutes();
	unsigned char* selectColor(CImgDisplay& window);
	bool isRouteSelected(float x, float y);
	Route* getSelectedRoute();
	//void addRoute();
};