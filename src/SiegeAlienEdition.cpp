#include "Game.h"
#include "Entitys.h"
#include "Screen.h"
#include "ControllerCollection.h"
#include "ScoreBoard.h"
#include "Menu.h"
#include "MenuController.h"
#include "State.h"
#include <SFML/Graphics.hpp>

#include <iostream>

int main () {
	// Create the game, scoreboard and menu
	si::model::Game* mainGame = new si::model::Game("game.xml");
	si::model::ScoreBoard scores = si::model::ScoreBoard("scores.xml");

	// Create a controller collection
	// We use this to update all controllers if the game is open
	si::controller::ControllerCollection controllerCollection = 
		si::controller::ControllerCollection();

	// Create a game screen
	si::view::Screen screen(mainGame);
	mainGame->registerObserver(std::shared_ptr<si::view::Screen>(&screen));

	// Create a state
	si::model::State generalState = si::model::State();

	// Create a menu controller and view
	si::controller::MenuController menu =
		si::controller::MenuController(&generalState,
	                                   mainGame,
	                                   &controllerCollection);
		
	si::view::Menu menuView = si::view::Menu(screen.window);

	// Run as long as our window is open
	while (screen.window->isOpen()) {
		// Lets first check to see if the user wants to quit
		// Process the quit event, the others are done in a controller
		sf::Event event;
		while (screen.window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				screen.window->close();

		// If we are in game we will draw that
		if (generalState.inGame()) {
			controllerCollection.update();
			mainGame->update();

		// Not in game; if the scoreboard is open draw that
		} else if (generalState.scoreBoardOpen()) {
			//scoreboardView->draw();

		// If all else fails, just show the menu
		} else {
			menuView.draw();
		}

		// Let the menucontroller do its thing
		menu.update();
	}
}