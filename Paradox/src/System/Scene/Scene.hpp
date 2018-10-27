#pragma once

// Entt
#include <entt/entity/registry.hpp>

// SFML
namespace sf
{
	class RenderTarget;
}

namespace paradox
{
	// Paradox
	class TransformSystem;
	class RenderSystem;

	class Scene
	{
	public:
		Scene();
		~Scene();

		// TODO: ability to add entities to the scene

		void loadScene(const std::string& path);
		void saveScene();
		void unloadScene();
		void update();
		void draw(sf::RenderTarget& target);
		void setName(const std::string& name);
		std::string getName() const;

	private:
		entt::registry<unsigned> m_entities;
		std::string m_name;
		std::unique_ptr<TransformSystem> m_transformSystem;
		std::unique_ptr<RenderSystem> m_renderSystem;
	};
}