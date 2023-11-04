#include "Vertice.h"

void Vertice::setX(float _x) {
	x = _x;
}

void Vertice::setY(float _y) {
	y = _y;
}

float Vertice::getX() {
	return x;
}

float Vertice::getY() {
	return y;
}

bool Vertice::contains(float x2, float y2) {
	return distance(x2, y2) < 10;
}

float Vertice::distance(float x2, float y2) {
	return sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
}

void Vertice::toString() {
	cout << x << ", " << y;
}