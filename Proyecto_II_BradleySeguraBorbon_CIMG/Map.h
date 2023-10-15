#pragma once
#include <iostream>
#include "Route.h"
#include "List.h"
#include "CImg.h"
#include "Button.h"

using namespace std;
using namespace cimg_library;

class Map {
	List<Route> routes;
	CImg<unsigned char> map;
	Button* addRouteButton;

public:
	Map();
	~Map() {}
	void displayMap();
	bool isClicking(float mouseX, float mouseY, Button& buttonPressed);
};