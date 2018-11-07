#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace paradox
{
	class ProjectDock;

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
		sf::RenderTexture m_sceneWindow;
		sf::RenderTexture m_gameWindow;
		std::string m_engineTitle;

		//
		// Should all docks be stored in a std::map/unordered in the end?
		// This could be stored by a singleton docking manager class
		std::unique_ptr<ProjectDock> m_projectDock;
		sf::Texture m_folderTexture;
		sf::Sprite m_folderIcon;
		//
	};
}