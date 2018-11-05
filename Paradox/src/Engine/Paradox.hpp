#pragma once

// C++
#include <filesystem>

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace fs = std::filesystem;

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
		void listProjectDirectory(const fs::path& pathToShow);

		sf::RenderWindow m_window;
		sf::RenderTexture m_sceneWindow;
		sf::RenderTexture m_gameWindow;
		std::string m_engineTitle;

		//
		sf::Texture m_folderTexture;
		sf::Sprite m_folderIcon;
		static std::string clickedNode;
		static bool selected;
	};
}