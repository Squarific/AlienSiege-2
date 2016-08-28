#ifndef SCOREBOARDVIEW
#define SCOREBOARDVIEW

#include "ScoreBoard.h"
#include <SFML/Graphics.hpp>

namespace si {
	namespace view {
		class ScoreBoardView {
		public:
			sf::Font font;
			sf::RenderWindow* window;
			si::model::ScoreBoard* scoreboard;

			ScoreBoardView();
			ScoreBoardView(sf::RenderWindow* window, si::model::ScoreBoard* scoreboard);

			void draw();
		};
	}
}

#endif