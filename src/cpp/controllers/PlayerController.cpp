#include "PlayerController.h"
#include "Errors.h"
#include <SFML/Graphics.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

si::controller::PlayerController::PlayerController () {
	throw NotEnoughArgumentsError();
}


si::controller::PlayerController::PlayerController (std::string xmlFile, std::shared_ptr< si::Ship > target) {
	this->target = target;

	pt::ptree tree;
	try {
		pt::read_xml(xmlFile, tree);
	} catch(std::exception const& error) {
		std::cerr << "Can't load playercontroller file '" << xmlFile << "'. Error: " << error.what();
	}

	this->left = static_cast<sf::Keyboard::Key>(tree.get("keys.left", 71));
	this->right = static_cast<sf::Keyboard::Key>(tree.get("keys.right", 72));
	this->fire = static_cast<sf::Keyboard::Key>(tree.get("keys.fire", 73));
}

void si::controller::PlayerController::update () {
	if (sf::Keyboard::isKeyPressed(this->left)) {
		this->target->setThrustX(-0.004f);
	}

	if (sf::Keyboard::isKeyPressed(this->right)) {
		this->target->setThrustX(0.004f);
	}

	// If both keys are pressed or none we dont want to thrust
	if (sf::Keyboard::isKeyPressed(this->left) ==
	    sf::Keyboard::isKeyPressed(this->right)) {
		this->target->setThrustX(0);
	}

	this->target->fireing = sf::Keyboard::isKeyPressed(this->fire);
}

void si::controller::PlayerController::onEvent (sf::Event event) {

}