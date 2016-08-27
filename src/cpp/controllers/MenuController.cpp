#include "MenuController.h"
#include "Errors.h"
#include <SFML/Graphics.hpp>

si::controller::MenuController () {
	throw si::NotEnoughArgumentsError();
}

si::controller::MenuController (si::model::State& generalState, si::model::Game& mainGame) {
	this->generalState = generalState;
	this->mainGame = mainGame;
}

void si::controller::update () {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
		this->generalState->setState("game");
		this->_setupSoloGame();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
		this->generalState->setState("game");
		this->_setupSoloGame();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->generalState->setState("score");
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->generalState->setState("menu");
		return;
	}
}