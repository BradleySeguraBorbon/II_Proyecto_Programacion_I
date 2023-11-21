//draw section for diplayMap()

/*if(addingRoute)
			background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *finishRouteButton->getButtonImage());
		else
			background.draw_image(addRouteButton->getX(), addRouteButton->getY(), *addRouteButton->getButtonImage());
		background.draw_image(saveRoutesButton->getX(), saveRoutesButton->getY(), *saveRoutesButton->getButtonImage());
		background.draw_image(loadRouteButton->getX(), loadRouteButton->getY(), *loadRouteButton->getButtonImage());*/


//draw method in route class
/*if (selectedVertice) {
		selectedVertice->draw(window, color, isSelected);
	}*/

	/*if (isSelected and !selectedVertice) {
		window.draw_circle(currentVertice->data->getX(), currentVertice->data->getY(), 8, color);
		window.draw_circle(currentVertice->data->getX(), currentVertice->data->getY(), 4, white);
	}
	else
		window.draw_circle(currentVertice->data->getX(), currentVertice->data->getY(), 3, color);*/

	/*if (isSelected and !selectedVertice) {
			window.draw_circle(currentVertice->next->data->getX(), currentVertice->next->data->getY(), 8, color);
			window.draw_circle(currentVertice->next->data->getX(), currentVertice->next->data->getY(), 4, white);
	}
		else
		window.draw_circle(currentVertice->next->data->getX(), currentVertice->next->data->getY(), 3, color);*/





//Get Selected Route --> Map Class

Route* getSelectedRoute(); //.h

Route* Map::getSelectedRoute() { //.cpp
	Node<Route>* currentRoute = routes.getHeadNode();
	while (currentRoute) {
		if (currentRoute->data->selected()) {
			return currentRoute->data;
		}
		currentRoute = currentRoute->next;
	}
}


//Animation
CImg<unsigned char>* newFrame = nullptr;
	Animation animation;
	string dir;

for (int i = 1; i <= 24; i++) {
		dir = "Resources/animation/" + to_string(i) + ".png";
		newFrame = new CImg<unsigned char>(dir.c_str());
		animation.pushBack(newFrame);
	}


#include <iostream>
#include "CImg.h"
#include "Node.h"
using namespace std;
using namespace cimg_library;

class Animation {
	Node<CImg<unsigned char>>* head;
	Node<CImg<unsigned char>>* currentFrame;

public:
	Animation() {}
	void pushBack(CImg<unsigned char>* newImage) {
		Node<CImg<unsigned char>>* newNode = new Node<CImg<unsigned char>>(newImage);
		Node<CImg<unsigned char>>* currentNode;
		if (!head) {
			head = newNode;
			head->next = head;
			currentFrame = head;
		}
		else {
			currentNode = head;
			while (currentNode->next != head) {
				currentNode = currentNode->next;
			}
			newNode->next = head;
			currentNode->next = newNode;
		}
	}
	CImg<unsigned char>* getCurrentFrame() {
		CImg<unsigned char>* image = currentFrame->data;
		currentFrame = currentFrame->next;
		return image;
	}
};