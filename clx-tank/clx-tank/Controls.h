#include <iostream>
#include <utility>

#pragma once
class Controls
{
	private:
		sf::Keyboard::Key moveUpKey;
		sf::Keyboard::Key moveDownKey;
		sf::Keyboard::Key moveLeftKey;
		sf::Keyboard::Key moveRightKey;
		bool moveUp;
		bool moveDown;
		bool moveLeft;
		bool moveRight;
		float movementXFactor;
		float movementYFactor;
		std::pair<std::pair<float, float>, std::pair<float, float>> movementLimits;
	public:
		Controls() {
			this->moveUp = false;
			this->moveDown = false;
			this->moveLeft = false;
			this->moveRight = false;
			this->movementXFactor = 0.1f;
			this->movementYFactor = 0.1f;
			this->moveUpKey = sf::Keyboard::Key::W;
			this->moveDownKey = sf::Keyboard::Key::S;
			this->moveLeftKey = sf::Keyboard::Key::A;
			this->moveRightKey = sf::Keyboard::Key::D;
			this->movementLimits = std::make_pair(std::make_pair(0.f, 0.f), std::make_pair(0.f, 0.f));
		}
		void setMoveKeys(const sf::Keyboard::Key up, const sf::Keyboard::Key down, const sf::Keyboard::Key left, const sf::Keyboard::Key right);
		std::pair< std::pair<float, float>, std::pair<float, float>> getMovementLimits();
		void setMovementFactor(const float x, const float y);
		sf::Vector2f getMovementResultVector();
		void setMovementLimits(const float minX, const float maxX, const float minY, const float maxY);
		bool inMovementArea(const sf::Vector2f position, const sf::Vector2f size);
		void bindMoveKeys();
};

void Controls::setMovementFactor(const float x, const float y) {
	this->movementXFactor = x;
	this->movementYFactor = y;
}

void Controls::setMoveKeys(const sf::Keyboard::Key up, const sf::Keyboard::Key down, const sf::Keyboard::Key left, const sf::Keyboard::Key right) {
	this->moveUpKey = up;
	this->moveDownKey = down;
	this->moveLeftKey = left;
	this->moveRightKey = right;
}

void Controls::bindMoveKeys() {
	this->moveUp = sf::Keyboard::isKeyPressed(this->moveUpKey);
	this->moveDown = sf::Keyboard::isKeyPressed(this->moveDownKey);
	this->moveLeft = sf::Keyboard::isKeyPressed(this->moveLeftKey);
	this->moveRight = sf::Keyboard::isKeyPressed(this->moveRightKey);
}

sf::Vector2f Controls::getMovementResultVector() {
	this->bindMoveKeys();
	sf::Vector2f vector(0.f, 0.f);
	if (this->moveUp)
		vector.y -= this->movementYFactor;
	if (this->moveDown)
		vector.y += this->movementYFactor;
	if (this->moveLeft)
		vector.x -= this->movementXFactor;
	if (this->moveRight)
		vector.x += this->movementXFactor;
	return vector;
}

void Controls::setMovementLimits(const float minX, const float maxX, const float minY, const float maxY) {
	this->movementLimits = std::make_pair(std::make_pair(minX, maxX), std::make_pair(minY, maxY));
}

std::pair<std::pair<float, float>, std::pair<float, float>> Controls::getMovementLimits() {
	return this->movementLimits;
}

bool Controls::inMovementArea(const sf::Vector2f position, const sf::Vector2f size) {
	return position.x >= this->movementLimits.first.first 
		&& position.x + size.x <= this->movementLimits.first.second
		&& position.y >= this->movementLimits.second.second
		&& position.y + size.y <= this->movementLimits.second.first;
}