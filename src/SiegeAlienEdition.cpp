#include "Game.h"
#include "Entitys.h"
#include "Screen.h"
#include "PlayerController.h"
#include "ControllerCollection.h"

int main () {
	// Create the game
	si::model::Game* mainGame = new si::model::Game("game.xml");

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

	// Create a screen
	si::view::Screen screen(mainGame);
	mainGame->registerObserver(std::shared_ptr<si::view::Screen>(&screen));

	mainGame->loadLevel(std::string("levels/level1.xml"));

	// Run the game as long as our window is open
	while (screen.window->isOpen()) {
		controllerCollection.update();
		mainGame->update();
	}
}