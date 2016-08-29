#include "ScoreInputView.h"
#include "Errors.h"

si::view::ScoreInputView::ScoreInputView () {
	throw NotEnoughArgumentsError();
}

si::view::ScoreInputView::ScoreInputView (sf::RenderWindow* window,
                                          si::controller::ScoreController* scoreController) {
	this->_window = window;
	this->_scoreController = scoreController;

	if (!this->_font.loadFromFile("fonts/NotoSans-Regular.ttf")) {
		throw new FontFileException();
	}
}

void si::view::ScoreInputView::draw () {
	// Set this window as the active openGl window
	this->_window->setActive();
	this->_window->clear();

	// Draw the return text
	sf::Text text;
	text.setString("What is your name? (Press enter to save)");

	text.setCharacterSize(24);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Regular);
	text.setFont(this->_font);

	this->_window->draw(text);

	unsigned int textSize = 24U;
	sf::Text name;
	name.setString(this->_scoreController->input);

	name.setCharacterSize(textSize);
	name.setColor(sf::Color::White);
	name.setStyle(sf::Text::Regular);
	name.setFont(this->_font);
	name.setPosition(sf::Vector2f(2 * textSize, this->_window->getSize().y / 2U));

	this->_window->draw(name);

	sf::Text scoreText;
	scoreText.setString(std::to_string(this->_scoreController->score));
	scoreText.setCharacterSize(textSize);
	scoreText.setColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Regular);
	scoreText.setFont(this->_font);
	scoreText.setPosition(sf::Vector2f(this->_window->getSize().x - 2 * textSize, this->_window->getSize().y / 2U));

	this->_window->draw(scoreText);

	// End the frame and draw it all
	this->_window->display();
}