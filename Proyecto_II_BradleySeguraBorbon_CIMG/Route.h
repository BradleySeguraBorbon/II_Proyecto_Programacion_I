#pragma once
#include <iostream>
#include <fstream>
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
	
	unsigned char red[3] = { 255, 1, 1 }, blue[3] = { 1, 1, 255 }, green[3] = { 1, 255, 1 };

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
	//Path* operator[](int path);
	void draw(CImg<unsigned char>& window);
};
