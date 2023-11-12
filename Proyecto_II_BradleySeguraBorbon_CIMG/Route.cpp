#include "Route.h"

//Path* Route::operator[](int path) {
//	try {
//		if (path >= 0) {
//			return &paths[path];
//		}
//		else throw(path);
//	}
//	catch (int value) {
//		cout << "Value " << value << " is not allowed: Allowed values are higher or equal than 0" << endl;
//	}
//	return nullptr;
//}

string Route::getName() {
	return name;
}

unsigned char* Route::getColor() {
	return color;
}

fstream& Route::getFile() {
	return file;
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
	currentVertice->data->draw(window, color, isSelected and !selectedVertice);
	while (currentVertice->next && show) {
		window.draw_line(currentVertice->data->getX(), currentVertice->data->getY(), currentVertice->next->data->getX(), currentVertice->next->data->getY(), color);
		window.draw_line(currentVertice->data->getX() + 0.001, currentVertice->data->getY() + 0.001, currentVertice->next->data->getX() + 0.001, currentVertice->next->data->getY() + 0.001, color);
		currentVertice = currentVertice->next;
	}
	currentVertice = vertices.getHeadNode();
	while (currentVertice->next && show) {
		currentVertice->next->data->draw(window, color, isSelected and !selectedVertice);
		currentVertice = currentVertice->next;
	}
}

void Route::saveRoute(fstream& file) {
	file << "Name: " << name << endl;
	file << "Color: " << to_string(color[0]) << "," << to_string(color[1]) << "," << to_string(color[2]) << endl;
	Node<Vertice>* currentVertice = vertices.getHeadNode();
	while (currentVertice) {
		file << currentVertice->data->getX() << "," << currentVertice->data->getY() << ";" << endl;
		currentVertice = currentVertice->next;
	}
}

void Route::loadRoute(string routeData) {
	string colorsLine, substring;
	Vertice* newVertice = nullptr;
	float x, y;
	int i = 0;

	int pos = routeData.find(' ');
	int endOfLine = routeData.find('\n');
	name = routeData.substr(pos + 1, endOfLine);
	routeData.erase(0, endOfLine + 1);
	cout << "This is the name: " << name << endl;
	cout << "This is the rest of the string: " << routeData << endl;

	pos = routeData.find(' ');
	endOfLine = routeData.find('\n');
	colorsLine = routeData.substr(pos + 1, endOfLine);
	routeData.erase(0, endOfLine + 1);

	while (i < 3) {
		pos = (i != 2 ?  colorsLine.find(',') : colorsLine.length()); 
		substring = colorsLine.substr(0, pos);
		color[i] = static_cast<unsigned char>(stoi(substring));
		colorsLine.erase(0, pos + 1);
		i++;
	}

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
		if (currentVertice->data->contains(x, y)) {
			if (isSelected and !selectedVertice) {
				currentVertice->data->setSelection(true);
				selectedVertice = currentVertice->data;
			}
			return true;
		}
		currentVertice = currentVertice->next;
	}
	return false;
}

void Route::toString() {
	cout << " --------------------------------------------------------------------" << endl;
	cout << "ROUTE NAME: " << name << endl;
	vertices.toString();
	cout << endl;
}