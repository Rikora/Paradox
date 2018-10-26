#include <System/TransformSystem.hpp>

// Paradox
#include <System/Component/ShapeRenderer.hpp>
#include <System/Component/Transform.hpp>

namespace paradox
{
	void TransformSystem::update(entt::registry<unsigned>& registry)
	{
		registry.view<ShapeRenderer, Transform>().each([](const auto, auto& render, auto& transform) 
		{
			render.shape->setPosition(transform.position);
			render.shape->setScale(transform.scale);
			render.shape->setRotation(transform.rotation);
		});
	}
}