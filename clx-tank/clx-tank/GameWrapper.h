#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include <iostream>

class GameWrapper
{
	private:
		std::vector<Player> players;
		std::vector<Enemy> enemies;
		sf::RenderWindow *window;
		int startTime;
		int lastEnemySpawnTime;
	public:
		GameWrapper() {
			this->startTime = time(NULL);
			this->window = nullptr;
			this->lastEnemySpawnTime = 0;
		}
		void setWindow(sf::RenderWindow& window);
		bool isRuning();
		void bindInputs();
		void addPlayer(Player& player);
		void update();
		void updatePlayers();
		void render();
		void renderPlayers();
		void spawnEnemies();
		int getElapsedTime();
};


void GameWrapper::setWindow(sf::RenderWindow& window) {
	this->window = &window;
}

void GameWrapper::addPlayer(Player& player) {
	this->players.push_back(player);
}

bool GameWrapper::isRuning() {
	return this->window->isOpen();
}

void GameWrapper::bindInputs() {
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}

void GameWrapper::update() {
	this->updatePlayers();
	this->spawnEnemies();
}

void GameWrapper::updatePlayers() {
	for (auto& player : this->players) {
		player.update();
	}
}

void GameWrapper::renderPlayers() {
	for (auto& player : this->players) {
		player.render(this->window);
	}
}

void GameWrapper::render() {
	this->window->clear();
	this->renderPlayers();
	this->window->display();
}

void GameWrapper::spawnEnemies() {
	int time = this->getElapsedTime();
	if (time % 10 != 0 || this->lastEnemySpawnTime == time) {
		return;
	}
	std::cout << "spwan" << std::endl;
	this->lastEnemySpawnTime = time;
}

int GameWrapper::getElapsedTime() {
	return time(NULL) - this->startTime;
}