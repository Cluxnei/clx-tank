#pragma once
#include <vector>
#include "Player.h"

class GameWrapper
{
	private:
		std::vector<Player> players;
		sf::RenderWindow *window;
	public:
		GameWrapper() {

		}
		void setWindow(sf::RenderWindow& window);
		bool isRuning();
		void bindInputs();
		void addPlayer(Player& player);
		void doPlayerControlsEventPropagation(sf::Event& event);
		void update();
		void updatePlayers();
		void render();
		void renderPlayers();
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

		this->doPlayerControlsEventPropagation(event);
	}
}

void GameWrapper::doPlayerControlsEventPropagation(sf::Event& event) {
	for (auto &player : this->players) {
		player.bindControlEvent(event);
	}
}

void GameWrapper::update() {
	this->updatePlayers();
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