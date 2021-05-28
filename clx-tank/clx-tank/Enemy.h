#pragma once
class Enemy
{
	private:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Sprite shape;
	public:
		Enemy() {
			this->position = sf::Vector2f(Utils::randomFloat(100.f, 1000), Utils::randomFloat(100.f, 800));
			this->velocity = sf::Vector2f(Utils::randomFloat(-0.5f, 0.5f), Utils::randomFloat(-0.1f, 0.1f));
			this->shape = sf::Sprite();
			this->shape.setPosition(this->position);
		}
		void setTexture(sf::Texture &texture);
		void render(sf::RenderWindow* window);
		void update();
};

void Enemy::setTexture(sf::Texture& texture) {
	this->shape.setTexture(texture);
}

void Enemy::render(sf::RenderWindow* window) {
	window->draw(this->shape);
}

void Enemy::update() {
	this->position += this->velocity;
	this->shape.setPosition(this->position);
}