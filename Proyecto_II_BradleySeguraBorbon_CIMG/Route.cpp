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
			currentPath->data->draw(window, red);
			currentPath = currentPath->next;
		}
		return;
	}
	window.draw_circle(currentPath->data->getStartPoint()->getX(), currentPath->data->getStartPoint()->getY(), 3, red);
}

void Route::saveRoute() {
	file.open(name + ".txt", ios::app);
	if (file.is_open()) {
		Node<Path>* currentPath = paths.getHeadNode();
		while (currentPath) {
			file << currentPath->data->getStartPoint()->getX() << "," << currentPath->data->getStartPoint()->getY() << ";" <<
				currentPath->data->getEndPoint()->getX() << "," << currentPath->data->getEndPoint()->getY() << endl;
			currentPath = currentPath->next;
		}
		file.close();
	}
}