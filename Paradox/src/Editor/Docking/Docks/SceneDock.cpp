#include <Editor/Docking/Docks/SceneDock.hpp>

// Paradox
#include <System/Scene/SceneManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	void SceneDock::update()
	{
		ImVec2 size = ImGui::GetContentRegionAvail();

		// Re-create scene texture if the docking size doesn't match
		if (m_sceneWindow.getSize() != sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)))
		{
			m_sceneWindow.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
		}
	}

	void SceneDock::draw(const sf::Color& color)
	{
		m_sceneWindow.clear(color);

		// Render to scene window
		SceneManager::getInstance()->draw(m_sceneWindow);

		m_sceneWindow.display();

		ImGui::Image(m_sceneWindow.getTexture());
	}
}