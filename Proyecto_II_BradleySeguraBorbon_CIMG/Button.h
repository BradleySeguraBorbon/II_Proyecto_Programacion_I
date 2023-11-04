#pragma once
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

class Button {
	CImg<unsigned char>* buttonImage;
	float x, y;
	bool isButtonAvailable;

public:
	Button() {}
	Button(CImg<unsigned char>* _buttonImage, float _x, float _y, bool isButtonAvailable) : buttonImage(_buttonImage), x(_x), y(_y), isButtonAvailable(isButtonAvailable) {}
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
	void setAvailability(bool isButtonAvailable);
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	CImg<unsigned char>* getButtonImage() {
		return buttonImage;
	}
	bool isAvailable();
	bool contains(float mouseX, float mouseY);
};
