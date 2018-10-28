#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

// Paradox
#include <System/Logic/RenderSystem.hpp>
#include <System/Logic/TransformSystem.hpp>
//#include <System/Scene/Scene.hpp>

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
		sf::RenderTexture m_sceneWindow;
		sf::RenderTexture m_gameWindow;

		// Temp placement
		entt::registry<unsigned> m_registry;
		RenderSystem m_renderSystem;
		TransformSystem m_transformSystem;
		//Scene m_scene;
	};
}