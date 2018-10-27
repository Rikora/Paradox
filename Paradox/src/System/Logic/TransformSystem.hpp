#pragma once

// Entt
#include <entt/entity/registry.hpp>

namespace paradox
{
	class TransformSystem
	{
	public:
		~TransformSystem() = default;

		void update(entt::registry<unsigned>& entities);
	};
}