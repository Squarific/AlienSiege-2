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
		if(event.KeyPressed == sf::Keyboard::BackSpace && this->input.size() != 0) {
			this->input.pop_back();
		} else if (event.KeyPressed == sf::Keyboard::Return && this->input.size() != 0) {
			this->_generalState->setState("scores");
			this->scores->add(this->input, this->score);
		} else if (event.text) {
			this->input += std::string(event.text);
		}
	}
}

void si::controller::ScoreController::notify (Observable& subject, std::string type) {
	if (type == std::string("gameover")) {
		this->input = std::string("");
		this->score = this->_game->score;
		this->_generalState->setState("scoreinput");
	}
}