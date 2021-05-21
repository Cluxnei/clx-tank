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
	public:
		Controls() {
			this->moveUp = false;
			this->moveDown = false;
			this->moveLeft = false;
			this->moveRight = false;
			this->movementXFactor = 1.f;
			this->movementYFactor = 1.f;
		}
		void setMoveKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
		void bindMoveKey(sf::Keyboard::Key key);
		void bindUnMoveKey(sf::Keyboard::Key key);
		void bindEvent(sf::Event& event);
		void setMovementFactor(float x, float y);
		sf::Vector2f getMovementResultVector();
};

void Controls::setMovementFactor(float x, float y) {
	this->movementXFactor = x;
	this->movementYFactor = y;
}

void Controls::setMoveKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right) {
	this->moveUpKey = up;
	this->moveDownKey = down;
	this->moveLeftKey = left;
	this->moveRightKey = right;
}

void Controls::bindEvent(sf::Event &event) {
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

void Controls::bindMoveKey(sf::Keyboard::Key key) {
	this->moveUp = key == this->moveUpKey;
	this->moveDown = key == this->moveDownKey;
	this->moveLeft = key == this->moveLeftKey;
	this->moveRight = key == this->moveRightKey;
}

void Controls::bindUnMoveKey(sf::Keyboard::Key key) {
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