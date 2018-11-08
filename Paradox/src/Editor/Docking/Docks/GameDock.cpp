#include <Editor/Docking/Docks/GameDock.hpp>

// Paradox
//#include <System/Scene/SceneManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	void GameDock::update()
	{
		ImVec2 size = ImGui::GetContentRegionAvail();

		// Re-create scene texture if the docking size does not match
		if (m_gameWindow.getSize() != sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)))
		{
			m_gameWindow.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
		}
	}

	void GameDock::draw(const sf::Color& color)
	{
		m_gameWindow.clear(color);

		// Render to game window
		//SceneManager::getInstance()->draw(m_gameWindow);

		m_gameWindow.display();

		ImGui::Image(m_gameWindow.getTexture());
	}
}