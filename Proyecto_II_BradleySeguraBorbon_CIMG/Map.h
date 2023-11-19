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
	Button* deleteVerticeButton;
	Button* colorsButton;

	unsigned char red[3] = { 255, 1, 1 }, blue[3] = { 1, 1, 255 }, green[3] = { 1, 255, 1 }, yellow[3] = { 255, 255, 0 }, cian[3] = { 0, 255, 255 },
		orange[3] = { 255, 60, 0 }, purple[3] = { 204, 0, 204 }, pink[3] = { 255, 51, 255 }, white[3] = { 255, 255, 255 };

public:
	Map();
	~Map() {}
	void displayMap();
	void manageRouteAdding(CImgDisplay& window, CImg<unsigned char>& background);
	void deleteSelectedRoute();
	void cancelSelection();
	void manageRouteVisibility();
	void deleteSelectedVertice();
	void manageRouteSelection();
	bool imageContains(CImg<unsigned char>& image, float imageX, float imageY, float mouseX, float mouseY);
	void drawRoutes(CImg<unsigned char>& window);
	unsigned char* selectColor(CImgDisplay& window, CImg<unsigned char>& background);
	bool isRouteSelected(float x, float y);
	Route* getSelectedRoute();
	void saveRoutes();
	void loadRoutes();
};