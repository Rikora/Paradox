#pragma once

// C++
#include <memory>

// SFML
#include <SFML/Graphics/Shape.hpp>

namespace paradox
{
	struct ShapeRenderer
	{
		std::unique_ptr<sf::Shape> shape;
	};
}