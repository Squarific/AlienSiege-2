#include "Game.h"
#include "Entitys.h"
#include "Screen.h"
#include "ControllerCollection.h"
#include "ScoreBoard.h"
#include "Menu.h"
#include "MenuController.h"
#include "State.h"
#include "ScoreBoardView.h"
#include <SFML/Graphics.hpp>

#include <iostream>

int main () {
	// Create the game, scoreboard and state
	si::model::Game* mainGame = new si::model::Game("game.xml");
	si::model::ScoreBoard scores = si::model::ScoreBoard("scores.xml");
	si::model::State generalState = si::model::State();

	// Create a controller collection
	// We use this to update all controllers if the game is open
	si::controller::ControllerCollection ingameControllerCollection = 
		si::controller::ControllerCollection();

	// Create the controller collection for the general stuff
	// These will receive all events and wil update every iteration
	si::controller::ControllerCollection controllerCollection =
		si::controller::ControllerCollection();

	// Create a menu controller
	

	// Create a shared pointer for the menu controller
	std::shared_ptr<si::controller::Controller> menuController = 
		std::shared_ptr<si::controller::Controller>(
			new si::controller::MenuController(&generalState,
			                                   mainGame,
			                                   &ingameControllerCollection));

	controllerCollection.controllers.push_back(menuController);

	// Create a game screen, a menuview and a view for the scores
	si::view::Screen screen(mainGame);
	mainGame->registerObserver(std::shared_ptr<si::view::Screen>(&screen));
	si::view::Menu menuView = si::view::Menu(screen.window);
	si::view::ScoreBoardView scoreBoardView = si::view::ScoreBoardView(screen.window, &scores);

	// Run as long as our window is open
	// This is the main loop
	while (screen.window->isOpen()) {
		// Lets first check to see if the user wants to quit
		// Process the quit event and user text input
		// Other input is done in the controllers
		bool closed = false;
		sf::Event event;
		while (screen.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen.window->close();
				closed = true;
			}

			controllerCollection.onEvent(event);
		}

		if (closed) break;

		// If we are in game we will draw that
		if (generalState.inGame()) {
			ingameControllerCollection.update();
			mainGame->update();

		// Not in game; if the scoreboard is open draw that
		} else if (generalState.scoreBoardOpen()) {
			scoreBoardView.draw();

		// If all else fails, just show the menu
		} else {
			menuView.draw();
		}

		// Let the menucontroller do its thing
		controllerCollection.update();
	}
}