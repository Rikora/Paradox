#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace paradox
{
	class Paradox
	{
	public:
		Paradox();
		~Paradox();

		void run();

	private:
		void pollEvents();
		void update(sf::Time dt);
		void render();

		sf::RenderWindow m_window;
		sf::CircleShape m_circle;
	};
}