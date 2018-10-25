#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

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
		sf::RenderTexture m_sceneWindow;
		sf::RenderTexture m_gameWindow;
	};
}