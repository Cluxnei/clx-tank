#include <iostream>

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
		float movementMinX;
		float movementMaxX;
		float movementMinY;
		float movementMaxY;
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
			this->movementMinX = 0.f;
			this->movementMaxX = 0.f;
			this->movementMinY = 0.f;
			this->movementMaxY = 0.f;
		}
		void setMoveKeys(const sf::Keyboard::Key up, const sf::Keyboard::Key down, const sf::Keyboard::Key left, const sf::Keyboard::Key right);
		void bindMoveKey(const sf::Keyboard::Key key);
		void bindUnMoveKey(const sf::Keyboard::Key key);
		void bindEvent(const sf::Event& event);
		void setMovementFactor(const float x, const float y);
		sf::Vector2f getMovementResultVector();
		void setMovementLimits(const float minX, const float maxX, const float minY, const float maxY);
		bool inMovementArea(const sf::Vector2f position, const sf::Vector2f size);
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

void Controls::bindEvent(const sf::Event &event) {
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			this->bindMoveKey(event.key.code);
		break;
		case sf::Event::KeyReleased:
			this->bindUnMoveKey(event.key.code);
		break;
		default:
		break;
	}
}

void Controls::bindMoveKey(const sf::Keyboard::Key key) {
	this->moveUp = key == this->moveUpKey;
	this->moveDown = key == this->moveDownKey;
	this->moveLeft = key == this->moveLeftKey;
	this->moveRight = key == this->moveRightKey;
}

void Controls::bindUnMoveKey(const sf::Keyboard::Key key) {
	this->moveUp = key == this->moveUpKey ? false : this->moveUp;
	this->moveDown = key == this->moveDownKey ? false : this->moveDown;
	this->moveLeft = key == this->moveLeftKey ? false : this->moveLeft;
	this->moveRight = key == this->moveRightKey ? false : this->moveRight;
}

sf::Vector2f Controls::getMovementResultVector() {
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
	this->movementMinX = minX;
	this->movementMaxX = maxX;
	this->movementMinY = minY;
	this->movementMaxY = maxY;
}

bool Controls::inMovementArea(const sf::Vector2f position, const sf::Vector2f size) {
	return position.x >= this->movementMinX 
		&& position.x + size.x <= this->movementMaxX
		&& position.y >= this->movementMaxY
		&& position.y + size.y <= this->movementMinY;
}