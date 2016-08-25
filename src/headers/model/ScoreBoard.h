#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <utility>

#include "Observers.h"

namespace si {
	namespace model {
		using Score = std::pair<std::string, int>;

		class ScoreBoard : Observable {
		private:
			std::vector<Score> scores;
		public:
			ScoreBoard();
			ScoreBoard(std::string xmlFile);

			// Load adds scores from a file to the current list
			// Save puts the current list in an xml file
			// No scores will be removed during both of these operations
			// Save overwrites the current file
			void load(std::string xmlFile);
			void save(std::string xmlFile);

			std::vector<Score> getScores();

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