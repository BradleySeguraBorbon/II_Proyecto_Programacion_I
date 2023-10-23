#include "Button.h"

bool Button::contains(float mouseX, float mouseY) {
	return mouseX > x and mouseX < x + buttonImage->width() and mouseY > y and mouseY < y + buttonImage->height();
}