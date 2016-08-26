#include "State.h"
#include <iostream>

si::model::State::State () {

}

bool si::model::State::inGame () {
	return this->_state == std::string("game");
}

bool si::model::State::scoreBoardOpen () {
	return this->_state == std::string("scores");
}

bool si::model::State::inMenu () {
	return this->_state == std::string("menu");
}

void si::model::State::setState (std::string state) {
	this->_state = state;
}