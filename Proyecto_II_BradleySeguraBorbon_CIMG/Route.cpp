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
	this->selectedVertice = selectedVertice;
}

void Route::addVertice(float x, float y) {
	Vertice* newVertice = new Vertice(x, y);
	vertices.pushBack(newVertice);
	newVertice = nullptr;
}

void Route::draw(CImg<unsigned char>& window) {
	unsigned char white[3] = { 255, 255, 255 };
	Node<Vertice>* currentVertice = vertices.getHeadNode();
	if (!currentVertice) return;
	/*if (selectedVertice) {
		selectedVertice->draw(window, color, isSelected);
	}*/
	currentVertice->data->draw(window, color, isSelected and !selectedVertice);
	/*if (isSelected and !selectedVertice) {
		window.draw_circle(currentVertice->data->getX(), currentVertice->data->getY(), 8, color);
		window.draw_circle(currentVertice->data->getX(), currentVertice->data->getY(), 4, white);
	}
	else
		window.draw_circle(currentVertice->data->getX(), currentVertice->data->getY(), 3, color);*/

	while (currentVertice->next && show) {
		window.draw_line(currentVertice->data->getX(), currentVertice->data->getY(), currentVertice->next->data->getX(), currentVertice->next->data->getY(), color);
		currentVertice->next->data->draw(window, color, isSelected and !selectedVertice);
		/*if (isSelected and !selectedVertice) {
			window.draw_circle(currentVertice->next->data->getX(), currentVertice->next->data->getY(), 8, color);
			window.draw_circle(currentVertice->next->data->getX(), currentVertice->next->data->getY(), 4, white);
		}
		else
			window.draw_circle(currentVertice->next->data->getX(), currentVertice->next->data->getY(), 3, color);*/
		currentVertice = currentVertice->next;
	}
}

void Route::saveRoute() {
	file.open(name + ".txt", ios::out);
	if (file.is_open()) {
		file << to_string(color[0]) << "," << to_string(color[1]) << "," << to_string(color[2]) << endl;
		Node<Vertice>* currentVertice = vertices.getHeadNode();
		while (currentVertice) {
			file << currentVertice->data->getX() << "," << currentVertice->data->getY() << endl;
			currentVertice = currentVertice->next;
		}
		file.close();
	}
	else
		cout << "ERROOOR";
}

void Route::loadRoute(string routeName) {
	string currentLine, substring;
	Vertice* newVertice = nullptr;
	float x, y;
	int i = 0, commaPosition;
	file.open(routeName + ".txt", ios::in);
	if (file.is_open()) {
		getline(file, currentLine);
		while (i < 3) {
			commaPosition = (i != 2 ?  currentLine.find(',') : currentLine.length()); 
			substring = currentLine.substr(0, commaPosition);
			color[i] = static_cast<unsigned char>(stoi(substring));
			if(i != 2) currentLine = currentLine.substr(commaPosition + 1, currentLine.length());
			i++;
		}
		while (getline(file, currentLine)) {
			commaPosition = currentLine.find(',');
			x = stof(currentLine.substr(0, commaPosition));
			y = stof(currentLine.substr(commaPosition + 1, currentLine.length()));
			newVertice = new Vertice(x, y);
			vertices.pushBack(newVertice);
			newVertice = nullptr;
		}
		file.close();
	}
	else
		cout << "ERROOOR";
	cout << x << "," << y << endl;
}

bool Route::contains(float x, float y) {
	Node<Vertice>* currentVertice = vertices.getHeadNode();
	while (currentVertice) {
		if (currentVertice->data->contains(x, y)) {
			if (isSelected) {
				currentVertice->data->setSelection(true);
				selectedVertice = currentVertice->data;
			}
			else
				isSelected = true;
			return true;
		}
		currentVertice = currentVertice->next;
	}
	return false;
}

void Route::toString() {
	cout << "ROUTE NAME: " << name << endl;
	vertices.toString();
}