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
		sf::Sprite background;
		int startTime;
		int lastElapsedTime;
		int lastEnemySpawnTime;
		sf::Texture enemyTexture;
	public:
		GameWrapper() {
			this->startTime = time(NULL);
			this->window = NULL;
			this->lastEnemySpawnTime = 0;
			this->lastElapsedTime = 0;
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
		void clearAndReallocateResources();
		void reallocShoots();
		void setBackgroundTexture(sf::Texture &texture);
		void setEnemyTexture(sf::Texture &texture);
		void updateEnemies();
		void renderEnemies();
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
	this->updateEnemies();
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
	this->window->draw(this->background);
	this->renderShoots();
	this->renderPlayers();
	this->renderEnemies();
	this->window->display();
}

void GameWrapper::spawnEnemies() {
	int time = this->getElapsedTime();
	if (time % 2 != 0 || this->lastEnemySpawnTime == time) {
		return;
	}
	Enemy *enemy = new Enemy();
	enemy->setTexture(this->enemyTexture);
	this->enemies.push_back(*enemy);
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

void GameWrapper::clearAndReallocateResources() {
	int elapesedTime = this->getElapsedTime();
	if (elapesedTime > this->lastElapsedTime) {
		if (elapesedTime % 2 == 0) {
			this->reallocShoots();
		}
		this->lastElapsedTime = elapesedTime;
	}
}

void GameWrapper::reallocShoots() {
	auto it = this->shoots.begin();
	while (it != this->shoots.end()) {
		if (!it->active) {
			it = this->shoots.erase(it);
			continue;
		}
		++it;
	}
}

void GameWrapper::setBackgroundTexture(sf::Texture& texture) {
	this->background.setTexture(texture);
}

void GameWrapper::setEnemyTexture(sf::Texture& texture) {
	this->enemyTexture = texture;
}

void GameWrapper::updateEnemies() {
	for (auto& enemy : this->enemies) {
		enemy.update();
	}
}

void GameWrapper::renderEnemies() {
	for (auto& enemy : this->enemies) {
		enemy.render(this->window);
	}
}