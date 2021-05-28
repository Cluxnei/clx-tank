#pragma once
#include <SFML/System/Vector2.hpp>
#include "Controls.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Utils.h"
#include "Shoot.h"

class Player
{
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Sprite shape;
		Controls controls;
		sf::Vector2f shootStartPoint;
		int shootsPerSecond;
		std::int64_t lastShootAt;
		float shootDelay;
	public:
		Player() {
			this->position = sf::Vector2f(0.f, 0.f);
			this->velocity = sf::Vector2f(1.f, 0.f);
			this->shootStartPoint = this->shape.getTransform().transformPoint(32, 16);
			this->shape = sf::Sprite();
			this->shape.setPosition(this->position);
			this->shootsPerSecond = 10;
			this->lastShootAt = Utils::currentTime();
			this->shootDelay = 1.f / this->shootsPerSecond * 1000;
		}
		void setPosition(float x, float y);
		void setVelocity(float x, float y);
		void setControls(Controls &controls);
		void setTexture(sf::Texture &texture);
		void update(sf::RenderWindow *window, std::vector<Shoot>& shoots, int elapsedTime);
		void render(sf::RenderWindow *window);
		void shoot(std::vector<Shoot>& shoots, sf::Vector2i mousePosition);
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

void Player::update(sf::RenderWindow* window, std::vector<Shoot>& shoots, int elapsedTime) {
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
	this->shootStartPoint = this->shape.getTransform().transformPoint(32, 16);
	if (Utils::currentTime() - this->lastShootAt >= this->shootDelay && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		this->shoot(shoots, mousePosition);
		this->lastShootAt = Utils::currentTime();
	}
}

void Player::render(sf::RenderWindow *window) {
	// sprite
	this->shape.setPosition(this->position);
	window->draw(this->shape);
	// shape
	//sf::RectangleShape r;
	//sf::FloatRect s = this->shape.getLocalBounds();
	//r.setSize(sf::Vector2f(s.width, s.height));
	//r.setFillColor(sf::Color::Green);
	//r.setPosition(sf::Vector2f(this->position.x, this->position.y));
	//Utils::setOriginAndReadjust(r, sf::Vector2f(8.f, 8.f));
	//r.setRotation(this->shape.getRotation());
	//window->draw(r);
	// sprite
	// shot origin
	//sf::CircleShape c(3.f);
	//c.setFillColor(sf::Color::Red);
	//c.setPosition(this->shootStartPoint);
	//window->draw(c);	
}

void Player::shoot(std::vector<Shoot>& shoots, sf::Vector2i mousePosition) {
	Shoot *s = new Shoot(this->shootStartPoint);
	s->setLimits(this->controls.getMovementLimits());
	s->setVelocity(Utils::normalize(sf::Vector2f(mousePosition.x, mousePosition.y) - this->shootStartPoint) * 2.f);
	s->setRotation(this->shape.getRotation());
	shoots.push_back(*s);
}