#pragma once
#include <iostream>
#include "Route.h"
#include "List.h"
#include "CImg.h"
#include "Button.h"
#include "Vertice.h"
#include <string>
#include <windows.h>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace cimg_library;
using namespace chrono;


class Map {
	List<Route> routes;
	CImg<unsigned char> map;
	Route* selectedRoute;
	fstream file;
	Button* addRouteButton;
	Button* finishRouteButton;
	Button* deleteRouteButton;
	Button* saveRoutesButton;
	Button* loadRouteButton;
	Button* showRouteButton;
	Button* hideRouteButton;
	Button* cancelSelectionButton;
	Button* changeColorButton;
	Button* deleteVerticeButton;
	Button* colorsButton;

public:
	Map();
	~Map();
	void displayMap();
	void manageRouteAdding(CImgDisplay& window, CImg<unsigned char>& background);
	void deleteSelectedRoute();
	void cancelSelection();
	void manageRouteVisibility();
	void deleteSelectedVertice();
	void manageRouteSelection();
	void changeSelectedRouteColor(CImgDisplay& window, CImg<unsigned char>& background);
	bool imageContains(CImg<unsigned char>& image, float imageX, float imageY, float mouseX, float mouseY);
	void drawRoutes(CImg<unsigned char>& window);
	unsigned char* selectColor(CImgDisplay& window, CImg<unsigned char>& background);
	bool isRouteSelected(float x, float y);
	void saveRoutes();
	void loadRoutes();
};