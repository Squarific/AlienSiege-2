#include "ScoreController.h"
#include "State.h"
#include "Errors.h"
#include "Game.h"
#include "ScoreBoard.h"

#include <SFML/Graphics.hpp>

si::controller::ScoreController::ScoreController () {
	throw NotEnoughArgumentsError();
}

si::controller::ScoreController::ScoreController (si::model::State* generalState,
                                                  si::model::Game* game,
                                                  si::model::ScoreBoard* scores) {
	this->_generalState = generalState;
	this->_game = game;
	this->_scores = scores;
}

void si::controller::ScoreController::update () {

}

void si::controller::ScoreController::onEvent (sf::Event event) {
	if (!this->_generalState->inputtingScore()) return;

	if (event.type == sf::Event::TextEntered){
		if(event.key.code == sf::Keyboard::BackSpace && this->_input.size() != 0) {
			this->_input.pop_back();
		} else if (event.key.code == sf::Keyboard::Return && this->_input.size() != 0) {
			this->_generalState->setState("scores");
			this->_scores->add(this->_input, this->_score);
		} else {
			this->_input += sf::String(event.text.unicode);
		}
	}
}

void si::controller::ScoreController::notify (Observable& subject, std::string type) {
	if (type == std::string("gameover")) {
		this->_input = std::string("");
		this->_score = this->_game->score;
		this->_generalState->setState("scoreinput");
	}
}