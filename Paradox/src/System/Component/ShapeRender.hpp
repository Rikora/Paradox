#pragma once

// C++
#include <memory>

// SFML
#include <SFML/Graphics/Shape.hpp>

namespace paradox
{
	struct ShapeRender
	{
		explicit ShapeRender(std::unique_ptr<sf::Shape> shape) :
		shape(std::move(shape))
		{
		}

		std::unique_ptr<sf::Shape> shape;
	};
}