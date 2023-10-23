#pragma once
#include <iostream>
#include "Vertice.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

class Path {
	Vertice* startPoint;
	Vertice* endPoint;

public:
	Path() : startPoint(nullptr), endPoint(nullptr) {}
	Path(Vertice* _startPoint, Vertice* _endPoint) : startPoint(_startPoint), endPoint(_endPoint) {}
	~Path() {}
	void setStartPoint(Vertice* _startPoint);
	void setEndPoint(Vertice* _endPoint);
	Vertice* getStartPoint();
	Vertice* getEndPoint();
	Vertice* operator[](int point);
	void draw(CImg<unsigned char>& window, unsigned char* color);
};
