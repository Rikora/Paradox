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
	class RenderSystem
	{
	public:
		~RenderSystem() = default;

		void update(entt::registry<unsigned>& entities, sf::RenderTarget& target);
	};
}