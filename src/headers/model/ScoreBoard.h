#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>

#include "Observers.h"

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

			void load(std::string xmlFile);
			void save(std::string xmlFile);

			pt::ptree getScores();

			void add(std::string name, int score);
			void reset();

			// Notify the observers that something about the subject changed
			virtual void notify(si::Observable& subject, std::string type);
			virtual void notifyObservers(std::string type);
			virtual void registerObserver(std::shared_ptr<si::Observer> observer);
		};
	}
}

#endif