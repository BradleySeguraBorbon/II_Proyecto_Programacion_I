#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "Path.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

class Route {
	List<Path> paths;
	string name;
	string color;
	fstream file;
	bool show;
	bool isSelected;
	
	unsigned char red[3] = { 255, 1, 1 }, blue[3] = { 1, 1, 255 }, green[3] = { 1, 255, 1 }, yellow[3] = { 255, 255, 0 }, cian[3] = { 0, 255, 255 },
		orange[3] = { 255, 60, 0 }, purple[3] = { 204, 0, 204 }, pink[3] = { 255, 51, 255 };

public:
	Route() {}
	Route(string _name, string _color) : name(_name), color(_color), show(true) {}
	Route(const Route& otherRoute) {
		paths = otherRoute.paths;
		name = otherRoute.name;
		color = otherRoute.color;
	}
	string getName();
	string getColor();
	fstream& getFile();
	Vertice* getFirstVertice();
	bool isShowing();
	void setName(string _name);
	void setColor(string _color);
	void setShow(bool _show);
	void addPath(Path* newPath) {
		paths.pushBack(newPath);
	}
	void saveRoute();
	void loadRoute(string routeName);
	//Path* operator[](int path);
	void draw(CImg<unsigned char>& window);
};
