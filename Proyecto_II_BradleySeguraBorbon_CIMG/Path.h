#pragma once
#include <iostream>
#include "Vertice.h"
using namespace std;

class Path {
	Vertice startPoint, endPoint;

public:
	Path() {}
	Path(Vertice _startPoint, Vertice _endPoint) : startPoint(_startPoint), endPoint(_endPoint) {}
	~Path() {}
	void setStartPoint(Vertice _startPoint);
	void setEndPoint(Vertice _endPoint);
	Vertice getStartPoint();
	Vertice getEndPoint();
	Vertice& operator[](int point);
};
