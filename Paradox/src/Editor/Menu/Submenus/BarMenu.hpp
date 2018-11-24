#pragma once

// SFML
#include <SFML/Graphics/Sprite.hpp>

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	class BarMenu final : public Menu
	{
	public:
		BarMenu();
		~BarMenu() = default;

		void update() override;
		void draw() override;

	private:
		void saveScene();

		sf::Sprite m_undoIcon;
		sf::Sprite m_redoIcon;
		sf::Sprite m_saveIcon;
		sf::Sprite m_playIcon;
		sf::Color m_grayBackgroundColor;
		bool m_playing; // Temp variable for editor modes
	};
}