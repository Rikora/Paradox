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
		auto editorEvent = EditorInputManager::getInstance();

		editorEvent->addEvent(EditorEvent::MiddleMousePress, thor::Action(sf::Mouse::Middle, thor::Action::PressOnce));
		editorEvent->addEvent(EditorEvent::MouseStrafing, thor::Action(sf::Mouse::Middle, thor::Action::Hold));
	}

	// TODO: remove this and place in update instead
	void SceneDock::pollEvents()
	{
		auto editorEvent = EditorInputManager::getInstance();

		// Get cursor start position
		if (editorEvent->isActive(EditorEvent::MiddleMousePress))
		{
			m_currentMousePos = m_relativeMousePos;
		}

		// Store previous mouse position as current for strafing
		m_previousMousePos = m_currentMousePos;

		// Check for strafing
		if (editorEvent->isActive(EditorEvent::MouseStrafing) && m_isFocused)
		{
			m_currentMousePos = m_relativeMousePos;
			const auto delta = sf::Vector2f(m_currentMousePos.x - m_previousMousePos.x, m_previousMousePos.y - m_currentMousePos.y);
			m_sceneView.move(delta);
		}
	}

	void SceneDock::update()
	{
		const auto size = ImGui::GetContentRegionAvail();
		m_relativeMousePos = sf::Vector2f(ImGui::GetMousePos()) - sf::Vector2f(ImGui::GetCursorScreenPos());

		// Check for window focus
		((m_relativeMousePos.x >= 0.f && m_relativeMousePos.x <= size.x) && (m_relativeMousePos.y >= 0.f && m_relativeMousePos.y <= size.y)) 
			? m_isFocused = true : m_isFocused = false;

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
		m_sceneWindow.clear(color);
		m_sceneWindow.setView(m_sceneView);

		// Render to scene window
		SceneManager::getInstance()->draw(m_sceneWindow);

		m_sceneWindow.display();

		ImGui::Image(m_sceneWindow.getTexture());
	}
}