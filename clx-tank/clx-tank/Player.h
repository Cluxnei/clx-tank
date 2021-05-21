#pragma once
#include <SFML/System/Vector2.hpp>
#include "Controls.h"

class Player
{
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::RectangleShape shape;
		Controls controls;
	public:
		Player() {
			this->position = sf::Vector2f(0.f, 0.f);
			this->velocity = sf::Vector2f(1.f, 0.f);
			this->shape = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
			this->shape.setPosition(this->position);
			this->shape.setFillColor(sf::Color::Green);
		}
		void setPosition(float x, float y);
		void setVelocity(float x, float y);
		void setControls(Controls &controls);
		void bindControlEvent(sf::Event& event);
		void update();
		void render(sf::RenderWindow *window);
};

void Player::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}

void Player::setVelocity(float x, float y) {
	this->velocity.x = x;
	this->velocity.y = y;
}

void Player::setControls(Controls &controls) {
	this->controls = controls;
}

void Player::bindControlEvent(sf::Event& event) {
	this->controls.bindEvent(event);
}

void Player::update() {
	this->velocity = this->controls.getMovementResultVector();
	this->position += this->velocity;
}

void Player::render(sf::RenderWindow *window) {
	this->shape.setPosition(this->position);
	window->draw(this->shape);
}