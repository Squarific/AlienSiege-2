#include "Game.h"
#include "Entitys.h"
#include "Screen.h"
#include "PlayerController.h"
#include "ControllerCollection.h"
#include "ScoreBoard.h"
#include <SFML/Graphics.hpp>

int main () {
	// Create the game, scoreboard and menu
	si::model::Game* mainGame = new si::model::Game("game.xml");
	si::model::ScoreBoard scores = si::model::ScoreBoard("scores.xml");

	// Create our player
	si::Ship* playerShip = new si::Ship("player.xml", true);

	// Add him to the game
	std::shared_ptr< si::Ship > player = std::shared_ptr< si::Ship >(playerShip);
	mainGame->addEntity(player);

	// Create a controller collection
	si::controller::ControllerCollection controllerCollection = 
		si::controller::ControllerCollection();

	// Create the controller for the player
	std::shared_ptr<si::controller::Controller> playerController = 
		std::shared_ptr<si::controller::Controller>(
			new si::controller::PlayerController(player));

	// And add the controller to our collection
	controllerCollection.controllers.push_back(playerController);

	// Create a game screen
	si::view::Screen screen(mainGame);
	mainGame->registerObserver(std::shared_ptr<si::view::Screen>(&screen));

	// mainGame->loadLevel(std::string("levels/level1.xml"));

	// Create a state
	si::model::State generalState = si::model::State();

	// Create a menu controller and view
	si::controller::Menu menu = si::controller::Menu(generalState, mainGame);
	si::view::Menu menuView = si::controller::Menu(screen.window);

	// Register our menu controller as an observer
	menuView.registerObserver(std::shared_ptr<si::view::Menu>(&menuView));

	// Run as long as our window is open
	while (screen.window->isOpen()) {
		// Lets first check to see if the user wants to quit
		// Process the quit event, the others are done in a controller
		sf::Event event;
		while (screen.window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				screen.window->close();

		// If we are in game we will draw that
		if (generalSate.inGame()) {
			controllerCollection.update();
			mainGame->update();

		// Not in game; if the scoreboard is open draw that
		} else if (state.scoreBoardOpen()) {
			scoreboardView->draw();

		// If all else fails, just show the menu
		} else {
			menuView->draw();
		}
	}
}