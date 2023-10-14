#pragma once
#include <iostream>
#include "Route.h"
#include "List.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

class Map {
	List<Route> routes;
	CImg<unsigned char> map;

public:
	Map();
	~Map() {}
	void displayMap();
	void isClicking(float mouseX, float mouseY, CImg<unsigned char>& object);
};