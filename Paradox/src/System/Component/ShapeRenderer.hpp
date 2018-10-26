#pragma once

// C++
#include <memory>

// SFML
#include <SFML/Graphics/Shape.hpp>

namespace paradox
{
	struct ShapeRenderer
	{
		explicit ShapeRenderer(std::unique_ptr<sf::Shape> shape) :
		shape(std::move(shape))
		{
		}

		std::unique_ptr<sf::Shape> shape;
	};
}