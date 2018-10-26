#include <System/RenderSystem.hpp>

// SFML
#include <SFML/Graphics/RenderTarget.hpp>

// Paradox
#include <System/Component/ShapeRenderer.hpp>

namespace paradox
{
	void RenderSystem::update(entt::registry<unsigned>& registry, sf::RenderTarget& target)
	{
		auto view = registry.view<ShapeRenderer>();

		for (const auto& entity : view)
		{
			auto& shape = view.get(entity);

			target.draw(*shape.shape.get());
		}
	}
}