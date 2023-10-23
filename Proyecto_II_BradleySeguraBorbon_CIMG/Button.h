#pragma once
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class Button {
	CImg<unsigned char>* buttonImage;
	float x, y;

public:
	Button() {}
	Button(CImg<unsigned char>* _buttonImage, float _x, float _y) : buttonImage(_buttonImage), x(_x), y(_y) {}
	~Button() {}
	void setButtonImage(CImg<unsigned char>* _buttonImage) {
		buttonImage = _buttonImage;
	}
	void setX(float _x) {
		x = _x;
	}
	void setY(float _y) {
		y = _y;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	CImg<unsigned char>* getButtonImage() {
		return buttonImage;
	}
	bool contains(float mouseX, float mouseY);
};
