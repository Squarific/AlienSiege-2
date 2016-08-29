#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Observers.h"
#include <SFML/Graphics.hpp>

namespace si {
	namespace controller {

		class Controller : public Observer {
		public:
			Controller();

			virtual void update();
			virtual void onEvent(sf::Event event);
			virtual void notify (Observable& subject, std::string type);
		};

	}
}

#endif