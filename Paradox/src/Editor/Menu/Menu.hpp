#pragma once

// SFML
#include <SFML/Window/Event.hpp>

namespace paradox
{
	// Menu base class
	class Menu
	{
	public:
		virtual ~Menu() {}

		//virtual void pollEvents(const sf::Event& event) = 0;
		//virtual void update() = 0;
		virtual void draw() = 0;
	};
}