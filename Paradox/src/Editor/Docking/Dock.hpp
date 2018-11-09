#pragma once

// SFML
#include <SFML/Graphics/Color.hpp>

namespace paradox
{
	// Dock base class
	class Dock
	{
	public:
		virtual ~Dock() {}

		virtual void update() {};
		virtual void draw() {};
		virtual void draw(const sf::Color& color) {}
	};
}