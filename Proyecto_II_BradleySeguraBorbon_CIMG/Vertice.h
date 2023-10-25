#pragma once
#include <iostream>
using namespace std;

class Vertice {
	float x, y;
	bool isSelected;

public:
	Vertice() : x(0), y(0) {}
	Vertice(float _x, float _y) : x(_x), y(_y) {}
	~Vertice() {}
	void setX(float _x);
	void setY(float _y);
	float getX();
	float getY();
};
