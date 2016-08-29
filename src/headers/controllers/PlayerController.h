#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <memory>
#include "Entitys.h"
#include "Controller.h"

namespace si {
	namespace controller {

		class PlayerController : public Controller {
		public:
			std::shared_ptr< si::Ship > target;
			sf::Keyboard::Key left;
			sf::Keyboard::Key right;
			sf::Keyboard::Key fire;

			PlayerController();
			PlayerController(std::string xmlFile, std::shared_ptr< si::Ship > target);

			virtual void update();
			virtual void onEvent(sf::Event event);
		};

	}
}

#endif /* PLAYERCONTROLLER_H */