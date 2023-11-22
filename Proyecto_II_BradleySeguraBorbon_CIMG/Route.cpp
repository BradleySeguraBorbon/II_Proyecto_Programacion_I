#include "Route.h"

string Route::getName() {
	return name;
}

unsigned char* Route::getColor() {
	return color;
}

Vertice* Route::getFirstVertice() {
	return vertices.getFirstElement();
}

bool Route::isShowing() {
	return show;
}

bool Route::selected() {
	return isSelected;
}

Vertice* Route::getSelectedVertice() {
	return selectedVertice;
}

void Route::setName(string _name) {
	name = _name;
}

void Route::setColor(unsigned char* _color) {
	color = _color;
}

void Route::setShow(bool _show) {
	show = _show;
}

void Route::setSelection(bool selection) {
	isSelected = selection;
}

void Route::setSelectedVertice(Vertice* selectedVertice) {
	if (!selectedVertice) this->selectedVertice->setSelection(false);
	this->selectedVertice = selectedVertice;
}

void Route::addVertice(float x, float y) {
	Vertice* newVertice = new Vertice(x, y);
	vertices.pushBack(newVertice);
	newVertice = nullptr;
}

void Route::deleteSelectedVertice() {
	if (selectedVertice) {
		vertices.deleteElement(selectedVertice);
		selectedVertice = nullptr;
	}
	
}

void Route::draw(CImg<unsigned char>& window) {
	unsigned char white[3] = { 255, 255, 255 };
	Node<Vertice>* currentVertice = vertices.getHeadNode();
	if (!currentVertice) return;
	currentVertice->getData()->draw(window, color, isSelected and !selectedVertice);
	while (currentVertice->getNext() && show) {
		window.draw_line(currentVertice->getData()->getX(), currentVertice->getData()->getY(), currentVertice->getNext()->getData()->getX(), currentVertice->getNext()->getData()->getY(), color);
		window.draw_line(currentVertice->getData()->getX() + 0.001, currentVertice->getData()->getY() + 0.001, currentVertice->getNext()->getData()->getX() + 0.001, currentVertice->getNext()->getData()->getY() + 0.001, color);
		currentVertice = currentVertice->getNext();
	}
	currentVertice = vertices.getHeadNode();
	while (currentVertice->getNext() && show) {
		currentVertice->getNext()->getData()->draw(window, color, isSelected and !selectedVertice);
		currentVertice = currentVertice->getNext();
	}
}

void Route::saveRoute(fstream& file) {
	file << "Name: " << name << endl;
	file << "Color: " << to_string(color[0]) << "," << to_string(color[1]) << "," << to_string(color[2]) << endl;
	file << "Shown: " << (show ? 1 : 0) << endl;
	Node<Vertice>* currentVertice = vertices.getHeadNode();
	while (currentVertice) {
		file << currentVertice->getData()->getX() << "," << currentVertice->getData()->getY() << endl;
		currentVertice = currentVertice->getNext();
	}
}

void Route::loadRoute(string routeData) {
	cout << "ROUTE DATA -- " << endl << routeData << endl;
	string colorsLine, substring;
	Vertice* newVertice = nullptr;
	float x, y;
	int i = 0, pos, endOfLine;

	pos = routeData.find(' ');
	endOfLine = routeData.find('\n');
	name = routeData.substr(pos + 1, endOfLine - (pos + 1));
	routeData.erase(0, endOfLine + 1);

	pos = routeData.find(' ');
	endOfLine = routeData.find('\n');
	colorsLine = routeData.substr(pos + 1, endOfLine - (pos + 1));
	routeData.erase(0, endOfLine + 1);

	while (i < 3) {
		pos = (i != 2 ?  colorsLine.find(',') : colorsLine.length()); 
		substring = colorsLine.substr(0, pos);
		color[i] = static_cast<unsigned char>(stoi(substring));
		colorsLine.erase(0, pos + 1);
		i++;
	}

	pos = routeData.find(' ');
	endOfLine = routeData.find('\n');
	show = stoi(routeData.substr(pos + 1, endOfLine - (pos + 1)));
	routeData.erase(0, endOfLine + 1);

	while (routeData != "") {
		pos = routeData.find(',');
		endOfLine = routeData.find('\n');
		x = stof(routeData.substr(0, pos));
		y = stof(routeData.substr(pos + 1, endOfLine));
		newVertice = new Vertice(x, y);
		vertices.pushBack(newVertice);
		newVertice = nullptr;
		routeData.erase(0, endOfLine + 1);
	}
}

bool Route::contains(float x, float y) {
	Node<Vertice>* currentVertice = vertices.getHeadNode();
	while (currentVertice) {
		if (currentVertice->getData()->contains(x, y)) {
			if (isSelected and !selectedVertice) {
				currentVertice->getData()->setSelection(true);
				selectedVertice = currentVertice->getData();
			}
			return true;
		}
		currentVertice = currentVertice->getNext();
	}
	return false;
}

void Route::toString() {
	cout << " --------------------------------------------------------------------" << endl;
	cout << "ROUTE NAME: " << name << endl;
	vertices.toString();
	cout << endl;
}

bool Route::isEmpty() {
	return !vertices.getHeadNode();
}