#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "CImg.h"
#include "Vertice.h"

using namespace std;
using namespace cimg_library;

class Route {
	List<Vertice> vertices;
	string name;
	unsigned char* color;
	fstream file;
	bool show;
	bool isSelected;

public:
	Route() {
		color = new unsigned char[3];
		show = true;
	}
	Route(string _name, unsigned char* _color) : name(_name), color(_color), show(true) {}
	Route(const Route& otherRoute) {
		vertices = otherRoute.vertices;
		name = otherRoute.name;
		color = otherRoute.color;
	}
	string getName();
	unsigned char* getColor();
	fstream& getFile();
	Vertice* getFirstVertice();
	bool isShowing();
	bool selected();
	void setName(string _name);
	void setColor(unsigned char* _color);
	void setShow(bool _show);
	void setSelection(bool selection);
	void addVertice(float x, float y);
	void saveRoute();
	void loadRoute(string routeName);
	//Path* operator[](int path);
	void draw(CImg<unsigned char>& window);
	bool contains(float x, float y);
	void toString();
};
