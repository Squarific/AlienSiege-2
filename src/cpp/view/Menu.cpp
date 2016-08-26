#include "Menu.h"
#include "Errors.h"

#include <SFML/Graphics.hpp>

si::view::Menu () {
	if (!this->font.loadFromFile("arial.ttf")) {
		throw new FontFileException();
	}
}

si::view::Menu (sf::RenderWindow* window) {
	this->window = window;

	if (!this->font.loadFromFile("arial.ttf")) {
		throw new FontFileException();
	}
}

si::view::draw () {
	// Set this window as the active openGl window
	this->window->setActive();
	this->window->clear();

	vector <std::string> options = {
		"Solo",
		"Coop",
		"Scores"
	};

	//center text
	sf::FloatRect textBounds = text.getLocalBounds();

	text.setOrigin(textBounds.left + textBounds.width / 2.0,
	               textBounds.top  + textBounds.height / 2.0);

	text.setPosition(this->window->getSize() / 2);

	// End the frame and draw it all
	this->window->display();
}

virtual void si::view::notify (si::Observable& subject, std::string type) {

}