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

string Route::getColor() {
	return color;
}

fstream& Route::getFile() {
	return file;
}

Vertice* Route::getFirstVertice() {
	return paths.getFirstElement()->getStartPoint();
}

bool Route::isShowing() {
	return show;
}

void Route::setName(string _name) {
	name = _name;
}

void Route::setColor(string _color) {
	color = _color;
}

void Route::setShow(bool _show) {
	show = _show;
}

void Route::draw(CImg<unsigned char>& window) {
	Node<Path>* currentPath = paths.getHeadNode();
	if (show) {
		while (currentPath) {
			currentPath->data->draw(window, pink);
			currentPath = currentPath->next;
		}
		return;
	}
	window.draw_circle(currentPath->data->getStartPoint()->getX(), currentPath->data->getStartPoint()->getY(), 3, yellow);
}

void Route::saveRoute() {
	file.open(name + ".txt", ios::out);
	if (file.is_open()) {
		Node<Path>* currentPath = paths.getHeadNode();
		while (currentPath) {
			file << currentPath->data->getStartPoint()->getX() << "," << currentPath->data->getStartPoint()->getY() << ";" <<
				currentPath->data->getEndPoint()->getX() << "," << currentPath->data->getEndPoint()->getY() << endl;
			currentPath = currentPath->next;
		}
		file.close();
	}
	else
		cout << "ERROOOR";
}

void Route::loadRoute(string routeName) {
	string currentLine, substring;
	Vertice** vertices = new Vertice * [2];
	Path* currentPath;
	int i = 0;
	file.open(routeName + ".txt", ios::in);
	if (file.is_open()) {
		while (getline(file, currentLine)) {
			while (i < 2) {
				vertices[i] = new Vertice();
				size_t commaPosition = currentLine.find(','), semiColonPosition = (i == 0 ? currentLine.find(';') : currentLine.size());
				substring = currentLine.substr(0, commaPosition);
				vertices[i]->setX(stof(substring));
				substring = currentLine.substr(commaPosition + 1, semiColonPosition);
				vertices[i]->setY(stof(substring));
				if(i == 0) 
					currentLine = currentLine.substr(semiColonPosition + 1, currentLine.size());
				i++;
			}
			currentPath = new Path(vertices[0], vertices[1]);
			paths.pushBack(currentPath);
			vertices[0] = nullptr;
			vertices[1] = nullptr;
			currentPath = nullptr;
			currentLine = "";
			i = 0;
		}
		file.close();
	}
	else
		cout << "ERROOOR";
}