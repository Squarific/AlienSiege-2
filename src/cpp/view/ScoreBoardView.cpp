#include "ScoreBoard.h"
#include "ScoreBoardView.h"
#include "Errors.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>

si::view::ScoreBoardView::ScoreBoardView () {
	throw NotEnoughArgumentsError();
}

si::view::ScoreBoardView::ScoreBoardView (sf::RenderWindow* window, si::model::ScoreBoard* scoreboard) {
	this->window = window;
	this->scoreboard = scoreboard;

	if (!this->font.loadFromFile("fonts/NotoSans-Regular.ttf")) {
		throw new FontFileException();
	}
}

void si::view::ScoreBoardView::draw () {
	// Set this window as the active openGl window
	this->window->setActive();
	this->window->clear();

	// Draw the return text
	sf::Text text;
	text.setString("Return to the menu using (esc)");

	text.setCharacterSize(24);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Regular);
	text.setFont(this->font);

	this->window->draw(text);

	std::vector <si::model::Score> scores = this->scoreboard->getScores();
	std::sort(scores.begin(), scores.end(), [](const si::model::Score& a, const si::model::Score& b) {
		return a.second > b.second;
	});

	int displayScores = 10;
	int counter = 0;
	int textSize = 24;

	for (auto& score : scores) {
		if (counter >= displayScores) break;

		sf::Text name;
		name.setString(score.first);

		name.setCharacterSize(textSize);
		name.setColor(sf::Color::White);
		name.setStyle(sf::Text::Regular);
		name.setFont(this->font);
		name.setPosition(sf::Vector2f(2 * textSize, 3 * textSize + 2 * textSize * counter));

		this->window->draw(name);

		sf::Text scoreText;
		scoreText.setString(std::to_string(score.second));
		scoreText.setCharacterSize(textSize);
		scoreText.setColor(sf::Color::White);
		scoreText.setStyle(sf::Text::Regular);
		scoreText.setFont(this->font);
		scoreText.setPosition(sf::Vector2f(this->window->getSize().x, 0) +
		                      sf::Vector2f(-2 * textSize, 3 * textSize + 2 * textSize * counter));

		this->window->draw(scoreText);
		counter++;
	}

	// End the frame and draw it all
	this->window->display();
}