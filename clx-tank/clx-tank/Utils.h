#pragma once
#include <SFML/Graphics.hpp>

class Utils
{
	public:
		static void setOriginAndReadjust(sf::Transformable& object, const sf::Vector2f& newOrigin);
};

void Utils::setOriginAndReadjust(sf::Transformable& object, const sf::Vector2f& newOrigin)
{
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
}