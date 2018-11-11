#pragma once

// SFML
#include <SFML/Graphics/RenderTexture.hpp>

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace paradox
{
	// TODO: save current view pos to file
	class SceneDock final : public Dock
	{
	public:
		SceneDock();
		~SceneDock() = default;

		virtual void pollEvents() override;
		virtual void update() override;
		virtual void draw(const sf::Color& color) override;

	private:
		sf::RenderTexture m_sceneWindow;
		sf::View m_sceneView;
		sf::Vector2f m_currentMousePos;
		sf::Vector2f m_previousMousePos;
		sf::Vector2f m_relativeMousePos;
		bool m_isFocused;
	};
}