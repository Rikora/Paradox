#pragma once

// SFML
#include <SFML/System/Vector2.hpp>

namespace paradox
{
	struct Transform
	{
		sf::Vector2f position;
		sf::Vector2f scale;
		float rotation;
	};
}
