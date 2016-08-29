#ifndef STATE_H
#define STATE_H

#include <iostream>

namespace si {
	namespace model {
		// This class will keep general state
		// It will tell us if we are in a game, in the scoreboard or in the menu
		class State {
			std::string _state = "menu";
		public:
			State();

			// State probe functions
			// These return a bool indicating where we are in that state
			bool inGame();
			bool scoreBoardOpen();
			bool inMenu();
			bool inputtingScore();

			// This function sets the general state
			// Possible state values are: 'game', 'menu', 'scores', 'scoreinput'
			void setState(std::string state);
		};
	}
}

#endif