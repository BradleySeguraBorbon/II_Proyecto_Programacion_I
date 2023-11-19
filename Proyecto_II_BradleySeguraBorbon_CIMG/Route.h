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
	bool show;
	bool isSelected;
	Vertice* selectedVertice;

public:
	Route() {
		name = "";
		color = new unsigned char[3];
		show = true;
		isSelected = false;
		selectedVertice = nullptr;
	}
	Route(string _name, unsigned char* _color) : name(_name), color(_color), show(true), isSelected(false), selectedVertice(nullptr) {}
	~Route() {}
	void setName(string _name);
	void setColor(unsigned char* _color);
	void setShow(bool _show);
	void setSelection(bool selection);
	void setSelectedVertice(Vertice* selectedVertice);
	string getName();
	unsigned char* getColor();
	bool isShowing();
	bool selected();
	Vertice* getSelectedVertice();
	Vertice* getFirstVertice();
	void addVertice(float x, float y);
	void deleteSelectedVertice();
	void saveRoute(fstream& file);
	void loadRoute(string routeData);
	void draw(CImg<unsigned char>& window);
	bool contains(float x, float y);
	void toString();
};
