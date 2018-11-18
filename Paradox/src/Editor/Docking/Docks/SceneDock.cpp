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
	m_isFocused(false),
	m_tileSize(16.f)
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
		
			// Vertical grid lines
			const auto multiple = 2;
			auto size = static_cast<unsigned>(std::round(m_sceneWindow.getSize().y / m_tileSize) * multiple);
			auto remainder = size % multiple;

			if (remainder != 0)
			{
				size = size + multiple - remainder;
				m_verticalLines.resize(size + multiple);
			}
			else
			{
				m_verticalLines.resize(size + multiple); 
			}

			float tileSize = 0.f;
			for (unsigned i = 0; i < m_verticalLines.size(); i += 2, tileSize += m_tileSize)
			{
				m_verticalLines[i] = sf::Vertex(sf::Vector2f(0.f, static_cast<float>(m_sceneWindow.getSize().y - tileSize)), sf::Color(100, 100, 100));
				m_verticalLines[i + 1] = sf::Vertex(sf::Vector2f(static_cast<float>(m_sceneWindow.getSize().x), static_cast<float>(m_sceneWindow.getSize().y - tileSize)), 
					sf::Color(75, 75, 75));
			}

			// Horizontal grid lines
			tileSize = 0.f;
			size = static_cast<unsigned>(std::round(m_sceneWindow.getSize().x / m_tileSize)) * multiple;
			remainder = size % multiple;

			if (remainder != 0)
			{
				size = size + multiple - remainder;
				m_horizontalLines.resize(size + multiple);
			}
			else
			{
				m_horizontalLines.resize(size + multiple);
			}

			for (unsigned i = 0; i < m_horizontalLines.size(); i += 2, tileSize += m_tileSize)
			{
				m_horizontalLines[i] = sf::Vertex(sf::Vector2f(tileSize, static_cast<float>(m_sceneWindow.getSize().y)), sf::Color(75, 75, 75));
				m_horizontalLines[i + 1] = sf::Vertex(sf::Vector2f(static_cast<float>(tileSize), 0.f), sf::Color(100, 100, 100));
			}
		}
	}

	void SceneDock::draw(const sf::Color& color)
	{
		m_sceneWindow.clear(sf::Color(60, 60, 60));
		m_sceneWindow.setView(m_sceneView);
		
		// TODO: store in a single vector instead
		// Draw grid lines
		m_sceneWindow.draw(m_verticalLines.data(), m_verticalLines.size(), sf::Lines);
		m_sceneWindow.draw(m_horizontalLines.data(), m_horizontalLines.size(), sf::Lines);

		// Render to scene window
		SceneManager::getInstance()->draw(m_sceneWindow);

		m_sceneWindow.display();

		ImGui::Image(m_sceneWindow.getTexture());
	}
}