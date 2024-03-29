#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Observers.h"

namespace si {
	namespace view {

		// This class creates a SFML window and will start drawing the game
		class Screen : public Observer {
		public:
			// The sfml window
			sf::RenderWindow* window;
			si::model::Game* game;

			// A screen should only be constructed using a game so the normal
			// constructor throws the NotEnoughArgumentsError error
			// The contructor also creates an sfml window
			Screen();
			Screen(si::model::Game* game);

			// Draws one frame on the created window
			void draw();

			virtual void notify (si::Observable& subject, std::string type);
		};

	}
}

#endif /* SCREEN_H */