#include "Path.h"

void Path::setStartPoint(Vertice* _startPoint) {
	startPoint = _startPoint;
}

void Path::setEndPoint(Vertice* _endPoint) {
	endPoint = _endPoint;
}

Vertice* Path::getStartPoint() {
	return startPoint;
}

Vertice* Path::getEndPoint() {
	return endPoint;
}

Vertice* Path::operator[](int point) {
	try {
		if (point >= 0 and point <= 1) {
			return (point == 0 ? startPoint : endPoint);
		}
		throw(point);
	}
	catch (int value) {
		cout << "Couldn´t get point " << value << " : allowed points are just 0 and 1" << endl;
	}
}

void Path::draw(CImg<unsigned char>& window, unsigned char* color) {
	window.draw_circle(startPoint->getX(), startPoint->getY(), 3, color);
	window.draw_line(startPoint->getX(), startPoint->getY(), endPoint->getX(), endPoint->getY(), color);
	window.draw_circle(endPoint->getX(), endPoint->getY(), 3, color);
}

