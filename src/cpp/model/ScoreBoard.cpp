#include "ScoreBoard.h"
#include "Errors.h"

#include <iostream>

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
	std::cout << "Loading scores from " << xmlFile << std::endl;

	pt::ptree tree;
	try {
		pt::read_xml(xmlFile, tree);
	} catch(std::exception const& error) {
		std::cerr << "Can't load scores file '" << xmlFile << "'. Error: " << error.what();
	}

	BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("scores")) {
		pt::ptree emptyTree;
		const pt::ptree& attributes = v.second.get_child("<xmlattr>", emptyTree);
		this->add(attributes.get("name", std::string("Anonymouse")), v.second.get_value<int>());
	}
}

void si::model::ScoreBoard::save (std::string xmlFile) {
	
}

pt::ptree si::model::ScoreBoard::getScores () {
	
}

void si::model::ScoreBoard::add(std::string name, int score) {
	this->notifyObservers();
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