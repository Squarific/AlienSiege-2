#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Errors.h"
#include "Entitys.h"
#include "StopWatch.h"

#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace pt = boost::property_tree;

si::model::Game::Game () {

}

si::model::Game::Game (int x, int y) {
	if (x < 1) throw new WorldSizeTooSmallError();
	if (y < 1) throw new WorldSizeTooSmallError();

	this->worldSize = {x, y};
}

si::model::Game::Game (std::string xmlFile) {
	
}

void si::model::Game::loadLevel (std::string filename) {
	std::cout << "Loading level " << filename << std::endl;

	pt::ptree tree;
	try {
		pt::read_xml(filename, tree);
	} catch(std::exception const&  error) {
		std::cerr << "Can't load player file '" << filename << "'. Error: " << error.what();
	}

	this->nextLevelFileName = tree.get("level.<xmlattr>.next", std::string());

	int x = tree.get("level.<xmlattr>.width", 1024);
	int y = tree.get("level.<xmlattr>.height", 786);
	this->worldSize = {x, y};

	// Load all enemies
	BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("level.enemies")) {
		pt::ptree emptyTree;
		const pt::ptree& attributes = v.second.get_child("<xmlattr>", emptyTree);
		this->_loadEnemy(v.second.data(), attributes);
	}

	std::cout << "Level " << filename << " loaded" << std::endl;
}

void si::model::Game::_loadEnemy (std::string texture, const pt::ptree& attributes) {
	std::shared_ptr<EnemyShip> enemy =
		std::shared_ptr<EnemyShip>(
			new si::EnemyShip(texture));

	double x = attributes.get("x", 50);
	double y = attributes.get("y", 50);

	int firespeed = attributes.get("firespeed", 500);

	double thrustpowerx = attributes.get("thrustpowerx", 0.2);
	double thrustpowery = attributes.get("thrustpowery", 0.2);

	enemy->setRotation(180);
	enemy->setPosition(x, y);
	enemy->setFireSpeed(firespeed);
	enemy->setMaxThrust(thrustpowerx, thrustpowery);
	enemy->bounceOffset = attributes.get("bounceoffset", 20);
	enemy->bulletTexture = attributes.get("bullettexture", std::string("assets/images/laser.png"));

	this->addEntity(enemy);
}

void si::model::Game::update () {
	int frames = this->stopWatch.getFrames();
	int calculatedFrames = frames;

	// This is safe because getFrames returns a number above or equal to 0
	while (frames--) {
		// ===== Add the entitys =====
		this->_handleAddObjects();

		// ===== Handle collisions =====
		this->_handleCollisions();

		// ===== Update all entitys =====
		for (auto& entity : this->objectPointers) {
			entity->update(this->stopWatch.getDeltaTime(), *this);
		}

		// ===== Remove objects =====
		this->_handleRemoveObjects();

		// ===== Check if we finished the level ====
		this->_handleFinish();
	}

	// If in the time we calculated the frames we now have to do more frames
	// than we calculated then we are starting to lagg behind, it this gets
	// too bad we will have to adjust the deltaTime
	if (this->stopWatch.getFramesWithoutReset() > calculatedFrames) {
		this->_laggTimes++;
	} else {
		this->_laggTimes--;
		if (this->_laggTimes < 0) this->_laggTimes = 0;
	}

	// If we lagg behind 5 times, we will raise the deltaTime
	if (this->_laggTimes > 5) {
		std::cerr
			<< "Your computer was too slow, physics are now less precise"
			<< std::endl;

		this->stopWatch.setDeltaTime(this->stopWatch.getDeltaTime() * 2);
	}

	this->notifyObservers();
}

void si::model::Game::_handleAddObjects () {
	for (auto entityPtr : this->addObjects) {
		// using vector for better readability
		auto& vec = this->objectPointers;

		if (std::find(vec.begin(), vec.end(), entityPtr) == vec.end()) {
			vec.push_back(entityPtr);
		}
	}

	this->addObjects.clear();
}

void si::model::Game::_handleRemoveObjects () {
	for (auto& entityPtr : this->deleteObjects) {
		// Delete it from the list

		auto& vec = this->objectPointers;
		vec.erase(
			std::remove(vec.begin(),
			            vec.end(),
			            this->getEntity(entityPtr)),
			vec.end()
		);
	}

	this->deleteObjects.clear();
}

void si::model::Game::_handleCollisions () {
	// If in the future the performance is a problem it is possible to
	// first contruct a spatial hashmap to reduce the amount of objects
	// we need to compare
	for (auto& entity1 : this->objectPointers) {
		sf::FloatRect bounds1 = entity1->sprite.getGlobalBounds();

		for (auto& entity2 : this->objectPointers) {
			// Don't compare with ourselves
			if (entity1 == entity2) break;

			sf::FloatRect bounds2 = entity2->sprite.getGlobalBounds();
			if (bounds1.intersects(bounds2)) {
				entity1->executeCollisionUsingMeOn(*entity2, *this);
			}
		}
	}
}

void si::model::Game::_handleFinish () {
	for (auto& entity : this->objectPointers) {
		// If there is still an enemy left, dont do anything
		if (entity->isEnemy()) {
			return;
		}
	}

	this->nextLevel();
}

void si::model::Game::nextLevel () {
	this->loadLevel(this->nextLevelFileName);
}

void si::model::Game::addEntity (std::shared_ptr< Entity > entityPtr) {
	this->addObjects.push_back(entityPtr);
}

void si::model::Game::removeEntity (Entity* entityPtr) {
	this->deleteObjects.push_back(entityPtr);
}

std::vector< std::shared_ptr< si::Entity >> si::model::Game::getObjects () {
	return this->objectPointers;
}

std::shared_ptr<si::Entity> si::model::Game::getEntity (si::Entity* entityPtr) {
	// Find the entity we want to remove
	for (auto& sharedEntityPtr : this->objectPointers) {

		// If they are the same
		if (sharedEntityPtr.get() == entityPtr) {

			return sharedEntityPtr;
		}
	}

	return std::shared_ptr<si::Entity>();
}

void si::model::Game::notifyObservers () {
	for (auto& observer : this->observers) {
		observer->notify(*this);
	}
};

void si::model::Game::registerObserver (std::shared_ptr<si::Observer> observer) {
	this->observers.push_back(observer);
}

void si::model::Game::clear () {
	this->objectPointers.clear();
};

std::vector<int> si::model::Game::getWorldSize () {
	return {
		this->worldSize.at(0),
		this->worldSize.at(1)
	};
}