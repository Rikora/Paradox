#include <Editor/Docking/Docks/SceneDock.hpp>

// Paradox
#include <Editor/Input/EditorInputManager.hpp>
#include <System/Scene/SceneManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	SceneDock::SceneDock() :
	m_isFocused(false)
	{
	}

	void SceneDock::update()
	{
		const auto size = ImGui::GetContentRegionAvail();

		// Check for window focus
		ImGui::IsMouseHoveringWindow() ? m_isFocused = true : m_isFocused = false;

		if (m_isFocused)
		{
			const auto editorEvent = EditorInputManager::getInstance();

			// Get cursor start position
			if (editorEvent->isActive(EditorEvent::MiddleMousePress))
			{
				m_currentMousePos = sf::Vector2f(ImGui::GetMousePos()) - sf::Vector2f(ImGui::GetCursorScreenPos());
			}

			// Store previous mouse position as current for strafing
			m_previousMousePos = m_currentMousePos;

			// Check for strafing
			if (editorEvent->isActive(EditorEvent::MouseStrafing))
			{
				m_currentMousePos = sf::Vector2f(ImGui::GetMousePos()) - sf::Vector2f(ImGui::GetCursorScreenPos());
				const auto delta = sf::Vector2f(m_currentMousePos.x - m_previousMousePos.x, m_previousMousePos.y - m_currentMousePos.y);
				m_sceneView.move(delta);
			}
		}

		// Re-create scene texture if the docking size doesn't match
		if (m_sceneWindow.getSize() != sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)))
		{
			m_sceneWindow.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
			m_sceneView.setCenter({ size.x / 2.f, size.y / 2.f });
			m_sceneView.setSize({ size.x, size.y });
		}
	}

	void SceneDock::draw(const sf::Color& color)
	{
		m_sceneWindow.clear(sf::Color(60, 60, 60));
		m_sceneWindow.setView(m_sceneView);

		// Render to scene window
		SceneManager::getInstance()->draw(m_sceneWindow);

		m_sceneWindow.display();

		ImGui::Image(m_sceneWindow.getTexture());

		//auto draw_list = ImGui::GetWindowDrawList();
		//const sf::Vector2f tileSize(16.f, 16.f);
		//const sf::Vector2f tilesetImagePos = sf::Vector2f(ImGui::GetWindowPos()) + sf::Vector2f(ImGui::GetCursorScreenPos().x, 0.f);

		//const auto xTiles = m_sceneWindow.getTexture().getSize().x / static_cast<unsigned>(tileSize.x);
		//const auto yTiles = m_sceneWindow.getTexture().getSize().y / static_cast<unsigned>(tileSize.y);

		//// Draw horizontal lines
		//for (unsigned x = 0; x < xTiles + 1; ++x)
		//{
		//	draw_list->AddLine(ImVec2(tilesetImagePos.x + x * tileSize.x, tilesetImagePos.y),
		//		ImVec2(tilesetImagePos.x + x * tileSize.x, tilesetImagePos.y + yTiles * tileSize.y),
		//		ImColor(130, 130, 130));
		//}

		//// Draw vertical lines
		//for (unsigned y = 0; y < yTiles + 1; ++y)
		//{
		//	draw_list->AddLine(ImVec2(tilesetImagePos.x, tilesetImagePos.y + y * tileSize.y),
		//		ImVec2(tilesetImagePos.x + xTiles * tileSize.x, tilesetImagePos.y + y * tileSize.y),
		//		ImColor(100, 100, 100));
		//}
	}
}