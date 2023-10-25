#pragma once
#include <iostream>
#include "Route.h"
#include "List.h"
#include "CImg.h"
#include "Button.h"
#include "Vertice.h"
#include <string>

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

public:
	Map();
	~Map() {}
	void displayMap();
	bool imageContains(float imageX, float imageY, CImg<unsigned char>&, float mouseX, float mouseY);
	bool isClicking(float mouseX, float mouseY, Button& buttonPressed);
	void drawRoutes(CImg<unsigned char>& window);
	void saveRoutes();
	//void addRoute();
};