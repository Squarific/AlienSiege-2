#include "ScoreBoard.h"
#include "Errors.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

si::model::ScoreBoard::ScoreBoard () {

}

si::model::ScoreBoard::ScoreBoard (std::string xmlFile) {
	this->load(xmlFile);
}

void si::model::ScoreBoard::load (std::string xmlFile) {

}

void si::model::ScoreBoard::save (std::string xmlFile) {
	
}

pt::ptree si::model::ScoreBoard::getScores () {
	
}

void si::model::ScoreBoard::add(std::string name, int score) {
	
}

void si::model::ScoreBoard::reset () {
	
}

void si::model::ScoreBoard::notifyObservers () {
	for (auto& observer : this->observers) {
		observer->notify(*this);
	}
};

void si::model::ScoreBoard::registerObserver (std::shared_ptr<si::Observer> observer) {
	this->observers.push_back(observer);
}