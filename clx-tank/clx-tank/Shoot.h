#include <SFML/Graphics.hpp>
#include <utility>
#pragma once

class Shoot
{
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		bool active;
		std::pair<std::pair<float, float>, std::pair<float, float>> movementLimits;
		sf::RectangleShape shape;
	public:
		Shoot(sf::Vector2f position) {
			this->position = position;
			this->velocity = sf::Vector2f(0.1f, 0.1f);
			this->active = true;
			this->movementLimits = std::make_pair(std::make_pair(0.f, 0.f), std::make_pair(0.f, 0.f));
			this->shape.setPosition(this->position);
			this->shape.setFillColor(sf::Color::Blue);
			this->shape.setSize(sf::Vector2f(10.f, 30.f));
		}
		void update();
		void render(sf::RenderWindow* window);
		void setLimits(std::pair<std::pair<float, float>, std::pair<float, float>> limits);
		bool inMovementArea();
		void setVelocity(sf::Vector2f velocity);
		void setRotation(float rotation);
};

void Shoot::update() {
	this->active = this->inMovementArea();
	if (!this->active) {
		return;
	}
	this->position += this->velocity;
	this->shape.setPosition(this->position);
}

void Shoot::render(sf::RenderWindow *window) {
	if (!this->active) {
		// return;
	}
	window->draw(this->shape);
}

void Shoot::setLimits(std::pair<std::pair<float, float>, std::pair<float, float>> limits) {
	this->movementLimits = limits;
}

bool Shoot::inMovementArea() {
	sf::Vector2f size = this->shape.getSize();
	return this->position.x >= this->movementLimits.first.first
		&& this->position.x + size.x <= this->movementLimits.first.second
		&& this->position.y >= this->movementLimits.second.second
		&& this->position.y + size.y <= this->movementLimits.second.first;
}

void Shoot::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}

void Shoot::setRotation(float rotation) {
	this->shape.setRotation(rotation);
}