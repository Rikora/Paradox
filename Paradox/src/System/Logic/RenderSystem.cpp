#include <System/Logic/RenderSystem.hpp>

// SFML
#include <SFML/Graphics/RenderTarget.hpp>

// Paradox
#include <System/Component/ShapeRenderer.hpp>

namespace paradox
{
	void RenderSystem::update(entt::registry<unsigned>& entities, sf::RenderTarget& target)
	{
		auto view = entities.view<ShapeRenderer>();

		for (const auto& entity : view)
		{
			auto& shape = view.get(entity);

			target.draw(*shape.shape.get());
		}
	}
}