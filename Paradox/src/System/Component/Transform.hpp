#pragma once

// SFML
#include <SFML/System/Vector2.hpp>

namespace paradox
{
	struct Transform
	{
		explicit Transform(const sf::Vector2f& position = sf::Vector2f(), 
						   const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f), float rotation = 0.f) :
		position(position),
		scale(scale),
		rotation(rotation)
		{
		}

		sf::Vector2f position;
		sf::Vector2f scale;
		float rotation;
	};
}
