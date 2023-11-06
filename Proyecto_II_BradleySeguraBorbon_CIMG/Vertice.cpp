#include "Vertice.h"

void Vertice::setX(float _x) {
	x = _x;
}

void Vertice::setY(float _y) {
	y = _y;
}

void Vertice::setSelection(bool isSelected) {
	this->isSelected = isSelected;
}

float Vertice::getX() {
	return x;
}

float Vertice::getY() {
	return y;
}

bool Vertice::selected() {
	return isSelected;
}

bool Vertice::contains(float x2, float y2) {
	return distance(x2, y2) < 8;
}

float Vertice::distance(float x2, float y2) {
	return sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
}

void Vertice::draw(CImg<unsigned char>& background, unsigned char* color, bool drawFilled) {
	unsigned char white[3] = { 255, 255, 255 };
	if (isSelected) {
		background.draw_circle(x, y, 8, white);
	}
	else if (drawFilled) {
		background.draw_circle(x, y, 8, color);
		background.draw_circle(x, y, 4, white);
	}
	else
		background.draw_circle(x, y, 4, color);
}

void Vertice::toString() {
	cout << x << ", " << y << endl;
}