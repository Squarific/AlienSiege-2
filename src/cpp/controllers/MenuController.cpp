#include "MenuController.h"
#include "Errors.h"
#include "PlayerController.h"
#include "Game.h"
#include "Entitys.h"
#include "ControllerCollection.h"
#include <SFML/Graphics.hpp>

si::controller::MenuController::MenuController () {
	throw si::NotEnoughArgumentsError();
}

si::controller::MenuController::MenuController (
	si::model::State* generalState,
    si::model::Game* mainGame,
    si::controller::ControllerCollection* controllerCollection) {

	this->_generalState = generalState;
	this->_mainGame = mainGame;
	this->_controllerCollection = controllerCollection;
}

void si::controller::MenuController::update () {
	if (this->_generalState->inMenu()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
			this->_generalState->setState("game");
			this->_setupSoloGame();
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
			this->_generalState->setState("game");
			this->_setupCoopGame();
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		    sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->_generalState->setState("scores");
			return;
		}
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->_generalState->setState("menu");
		return;
	}
}

void si::controller::MenuController::_setupSoloGame () {
	// First reset the game and the controller collection
	this->_mainGame->clear();
	this->_controllerCollection->controllers.clear();

	// Create our player
	si::Ship* playerShip = new si::Ship("playerprops1.xml", true);

	// Add him to the game
	std::shared_ptr< si::Ship > player = std::shared_ptr< si::Ship >(playerShip);
	this->_mainGame->addEntity(player);

	// Create the controller for the player
	std::shared_ptr<si::controller::Controller> playerController = 
		std::shared_ptr<si::controller::Controller>(
			new si::controller::PlayerController("player1.xml", player));

	// And add the controller to our collection
	this->_controllerCollection->controllers.push_back(playerController);

	this->_mainGame->loadLevel(std::string("levels/level1.xml"));
}

void si::controller::MenuController::_setupCoopGame () {
	// First reset the game and the controller collection
	this->_mainGame->clear();
	this->_controllerCollection->controllers.clear();

	// Create our players
	si::Ship* playerShip1 = new si::Ship("playerprops1.xml", true);
	si::Ship* playerShip2 = new si::Ship("playerprops2.xml", true);

	// Add them to the game
	std::shared_ptr< si::Ship > player1 = std::shared_ptr< si::Ship >(playerShip1);
	this->_mainGame->addEntity(player1);

	std::shared_ptr< si::Ship > player2 = std::shared_ptr< si::Ship >(playerShip2);
	this->_mainGame->addEntity(player2);

	// Create the controller for the players
	std::shared_ptr<si::controller::Controller> playerController1 = 
		std::shared_ptr<si::controller::Controller>(
			new si::controller::PlayerController("player1.xml", player1));

	std::shared_ptr<si::controller::Controller> playerController2 = 
		std::shared_ptr<si::controller::Controller>(
			new si::controller::PlayerController("player2.xml", player2));

	// And add the controllers to our collection
	this->_controllerCollection->controllers.push_back(playerController1);
	this->_controllerCollection->controllers.push_back(playerController2);

	this->_mainGame->loadLevel(std::string("levels/level1.xml"));
}

void si::controller::MenuController::onEvent (sf::Event event) {

}