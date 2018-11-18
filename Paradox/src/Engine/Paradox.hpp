#pragma once

// Sol
//#include <sol/sol.hpp>

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
		sf::Sprite m_undoIcon;
		sf::Sprite m_redoIcon;
		sf::Sprite m_saveIcon;
		//sol::state m_lua;
	};
}