#pragma once
class Enemy
{
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Sprite shape;
	public:
		Enemy() {
			this->position = sf::Vector2f(0.f, 0.f);
			this->velocity = sf::Vector2f(0.f, 0.f);
			this->shape = sf::Sprite();
			this->shape.setPosition(this->position);
		}
};

