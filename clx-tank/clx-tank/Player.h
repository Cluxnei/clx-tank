#pragma once
#include <SFML/System/Vector2.hpp>
#include "Controls.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Utils.h"

class Player
{
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Sprite shape;
		Controls controls;
	public:
		Player() {
			this->position = sf::Vector2f(0.f, 0.f);
			this->velocity = sf::Vector2f(1.f, 0.f);
			this->shape = sf::Sprite();
			this->shape.setPosition(this->position);
		}
		void setPosition(float x, float y);
		void setVelocity(float x, float y);
		void setControls(Controls &controls);
		void setTexture(sf::Texture &texture);
		void update(sf::RenderWindow *window);
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

void Player::setTexture(sf::Texture &texture) {
	this->shape.setTexture(texture);
}

void Player::update(sf::RenderWindow *window) {
	this->velocity = this->controls.getMovementResultVector();
	sf::Vector2u textureSize = this->shape.getTexture()->getSize();
	const sf::Vector2f size(textureSize.x, textureSize.y);
	if (this->controls.inMovementArea(this->position + this->velocity, size)) {
		this->position += this->velocity;
	}
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	float diffOrigin = 8.f;
	float dx = mousePosition.x - this->position.x + diffOrigin * 2;
	float dy = mousePosition.y - this->position.y - diffOrigin * 2;
	float angle = (atan2(dy, dx) + M_PI / 2.f) * 180.f / M_PI;
	Utils::setOriginAndReadjust(this->shape, sf::Vector2f(diffOrigin, diffOrigin));
	this->shape.setRotation(angle);
}

void Player::render(sf::RenderWindow *window) {
	this->shape.setPosition(this->position);	
	window->draw(this->shape);
}