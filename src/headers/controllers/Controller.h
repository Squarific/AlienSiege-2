#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

namespace si {
	namespace controller {

		class Controller {
		public:
			Controller();

			virtual void update();
			virtual void onEvent(sf::Event event);		
		};

	}
}

#endif