#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "State.h"
#include "Game.h"

namespace si {
	namespace controller {
		class MenuController {
		private:
			si::model::State& generalState;
			si::model::Game& mainGame;
		public:
			// The contructor without arguments throws a NotEnoughArgumentsError
			MenuController();
			MenuController(si::model::State& generalState, si::model::Game& mainGame);

			// Check for user input
			// Should be called about every frame
			void update();
		};
	}
}

#endif