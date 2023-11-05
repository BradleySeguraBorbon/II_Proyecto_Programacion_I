#pragma once
#include <iostream>
#include <cmath>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class Vertice {
	float x, y;
	bool isSelected;

public:
	Vertice() : x(0), y(0), isSelected(false) {}
	Vertice(float _x, float _y) : x(_x), y(_y), isSelected(false) {}
	~Vertice() {}
	void setX(float _x);
	void setY(float _y);
	void setSelection(bool isSelected);
	float getX();
	float getY();
	bool selected();
	bool contains(float x2, float y2);
	float distance(float x2, float y2);
	void draw(CImg<unsigned char>& background, unsigned char* color, bool drawFilled);
	void toString();
};
