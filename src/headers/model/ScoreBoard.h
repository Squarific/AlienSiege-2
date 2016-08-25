#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

namespace si {
	namespace model {
		class ScoreBoard : Observable {
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

			// Notify the observers that something about the subject changed
			virtual void notifyObservers();
			virtual void registerObserver(std::shared_ptr<si::Observer> observer);
		};
	}
}

#endif