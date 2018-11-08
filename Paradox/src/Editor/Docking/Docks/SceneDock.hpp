#pragma once

// SFML
#include <SFML/Graphics/RenderTexture.hpp>

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace paradox
{
	class SceneDock final : public Dock
	{
	public:
		~SceneDock() = default;

		virtual void update() override;
		virtual void draw(const sf::Color& color) override;

	private:
		sf::RenderTexture m_sceneWindow;
	};
}