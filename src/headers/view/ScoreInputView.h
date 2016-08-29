#ifndef SCOREINPUTVIEW_H
#define SCOREINPUTVIEW_H

#include "ScoreController.h"
#include <SFML/Graphics.hpp>

namespace si {
	namespace view {
		class ScoreInputView {
		private:
			sf::RenderWindow* _window;
			si::controller::ScoreController* _scoreController;
			sf::Font _font;

		public:
			ScoreInputView();
			ScoreInputView(sf::RenderWindow* window,
			               si::controller::ScoreController* scoreController);

			void draw();
		};
	}
}

#endif