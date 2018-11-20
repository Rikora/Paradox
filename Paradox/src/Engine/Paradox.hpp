#pragma once

// Sol
//#include <sol/sol.hpp>

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
		void pollEvents(sf::RenderWindow& window);
		void update(sf::Time dt);
		void updateGUI(sf::RenderWindow& window, sf::Time dt);
		void render(sf::RenderWindow& window);

		std::string m_engineTitle;
		//sol::state m_lua;
	};
}