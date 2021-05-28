#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Shoot.h"
#include <iostream>

class GameWrapper
{
	private:
		std::vector<Player> players;
		std::vector<Enemy> enemies;
		std::vector<Shoot> shoots;
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
		void updateShoots();
		void renderShoots();
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
	this->updateShoots();
}

void GameWrapper::updatePlayers() {
	for (auto& player : this->players) {
		player.update(this->window, this->shoots, this->getElapsedTime());
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
	this->renderShoots();
	this->window->display();
}

void GameWrapper::spawnEnemies() {
	int time = this->getElapsedTime();
	if (time % 10 != 0 || this->lastEnemySpawnTime == time) {
		return;
	}
	// Spawn
	this->lastEnemySpawnTime = time;
}

int GameWrapper::getElapsedTime() {
	return time(NULL) - this->startTime;
}

void GameWrapper::updateShoots() {
	for (auto& shoot : this->shoots) {
		shoot.update();
	}
}

void GameWrapper::renderShoots() {
	for (auto& shoot : this->shoots) {
		shoot.render(this->window);
	}
}