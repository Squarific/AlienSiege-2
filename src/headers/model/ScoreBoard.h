#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

namespace si {
	namespace model {
		class ScoreBoard {
		private:
			pt::ptree scores;
		public:
			ScoreBoard();
			ScoreBoard(std::string xmlFile);
			~ScoreBoard();

			load(std::string xmlFile);
			save(std::string xmlFile);

			pt::ptree getScores();

			add(std::string name, int score);
			reset();
		};
	}
}

#endif