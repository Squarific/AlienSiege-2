#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "State.h"
#include "Game.h"
#include "ControllerCollection.h"
#include "Controller.h"

namespace si {
	namespace controller {
		class MenuController : public Controller {
		private:
			si::model::State* _generalState;
			si::model::Game* _mainGame;
			si::controller::ControllerCollection* _controllerCollection;

			void _setupSoloGame();
		public:
			// The contructor without arguments throws a NotEnoughArgumentsError
			MenuController();
			MenuController(si::model::State* generalState,
			               si::model::Game* mainGame,
			               si::controller::ControllerCollection* controllerCollection);

			// Check for user input
			// Should be called about every frame
			virtual void update();
			virtual void onEvent(sf::Event event);
		};
	}
}

#endif