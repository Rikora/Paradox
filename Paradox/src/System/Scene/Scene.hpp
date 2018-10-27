#pragma once

// Entt
#include <entt/entity/registry.hpp>

namespace paradox
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		// Scene manager?
		void loadScene();
		void unloadScene();
		//

		void setName(const std::string& name);
		std::string getName() const;

	private:
		entt::registry<unsigned> m_entities;
		std::string m_name;
	};
}