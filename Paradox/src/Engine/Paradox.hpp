#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>

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
		void updateGUI(sf::Time dt);
		void render();

		sf::RenderWindow m_window;
		std::string m_engineTitle;
	};
}