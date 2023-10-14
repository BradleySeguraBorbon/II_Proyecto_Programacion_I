#pragma once
#include <iostream>
#include <fstream>
#include "List.h"
#include "Path.h"
using namespace std;

class Route {
	List<Path> paths;
	string name;
	string color;
	fstream file;

public:
	Route() {}
	Route(string _name, string _color, Path startPath) : name(_name), color(_color) {
		paths.pushBack(startPath);
	}
	Route(const Route& otherRoute) {
		paths = otherRoute.paths;
		name = otherRoute.name;
		color = otherRoute.color;
	}
	//Path& operator[](int path);

};
