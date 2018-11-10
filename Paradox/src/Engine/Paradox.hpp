#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>

// Thor
#include <Thor/Input/ActionMap.hpp>

namespace paradox
{
	class Paradox
	{
	public:
		Paradox();
		~Paradox();

		void run();

	private:
		void pollEvents(sf::RenderWindow& window);
		void update(sf::Time dt);
		void updateGUI(sf::RenderWindow& window, sf::Time dt);
		void render(sf::RenderWindow& window);

		std::string m_engineTitle;
		thor::ActionMap<std::string> m_actions;
	};
}