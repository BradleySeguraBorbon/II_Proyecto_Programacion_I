#include "Button.h"

void Button::setAvailability(bool isButtonAvailable) {
	this->isButtonAvailable = isButtonAvailable;
}

bool Button::contains(float mouseX, float mouseY) {
	return mouseX > x and mouseX < x + buttonImage->width() and mouseY > y and mouseY < y + buttonImage->height();
}

bool Button::isAvailable() {
	return isButtonAvailable;
}