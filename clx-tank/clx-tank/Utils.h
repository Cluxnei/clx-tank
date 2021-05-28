#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>

class Utils
{
	public:
		static void setOriginAndReadjust(sf::Transformable& object, const sf::Vector2f& newOrigin);
		static sf::Vector2f normalize(sf::Vector2f vector);
		static std::int64_t currentTime();
		static float randomFloat(float min, float max);
};

void Utils::setOriginAndReadjust(sf::Transformable& object, const sf::Vector2f& newOrigin)
{
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
}

sf::Vector2f Utils::normalize(sf::Vector2f vector) {
	float mag = hypot(vector.x, vector.y);
	vector.x /= mag;
	vector.y /= mag;
	return vector;
}

std::int64_t Utils::currentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

float Utils::randomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}