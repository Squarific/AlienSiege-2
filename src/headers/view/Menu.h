#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "Observers.h"

#include <iostream>

#include <SFML/Graphics.hpp>

namespace si {
	namespace view {
		class Menu {
		public:
			sf::RenderWindow* window;
			sf::Font font;

			Menu();
			Menu(sf::RenderWindow* window);

			void draw ();
		};
	}
}

#endif