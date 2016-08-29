#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include "Controller.h"
#include "State.h"
#include "Game.h"
#include "ScoreBoard.h"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace si {
	namespace controller {
		class ScoreController : public Controller {
		private:
			si::model::State* _generalState;
			si::model::Game* _game;
			si::model::ScoreBoard* _scores;

			std::string _input;
			int _score = 0;

		public:
			ScoreController();
			ScoreController(si::model::State* generalState, si::model::Game* game, si::model::ScoreBoard* scores);

			// Check for user input
			// Should be called about every frame
			virtual void update();
			virtual void onEvent(sf::Event event);
			virtual void notify (Observable& subject, std::string type);
		};
	}
}

#endif