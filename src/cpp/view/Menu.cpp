#include "Menu.h"
#include "Errors.h"
#include "Observers.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

si::view::Menu::Menu () {
	throw NotEnoughArgumentsError();
}

si::view::Menu::Menu (sf::RenderWindow* window) {
	this->window = window;

	if (!this->font.loadFromFile("fonts/arial.ttf")) {
		throw new FontFileException();
	}
}

void si::view::Menu::draw () {
	// Set this window as the active openGl window
	this->window->setActive();
	this->window->clear();

	std::vector <std::string> options = {
		"Solo",
		"Coop",
		"Scores"
	};

	float startHeight = options.size() * 2.0f;
	int counter = 0;
	int textSize = 24;
	for (auto& option : options) {
		sf::Text text;
		text.setString(option);

		text.setCharacterSize(24);
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Regular);
		text.setFont(this->font);

		//center text
		sf::FloatRect textBounds = text.getLocalBounds();

		text.setOrigin(textBounds.left + textBounds.width / 2.0f,
		               textBounds.top  + textBounds.height / 2.0f);

		text.setPosition(sf::Vector2f(this->window->getSize() / 2U) +
		                 sf::Vector2f(0, -startHeight * textSize + 2 * textSize * counter));

		this->window->draw(text);
		counter++;
	}

	// End the frame and draw it all
	this->window->display();
}