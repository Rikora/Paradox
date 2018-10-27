#include <System/Scene/Scene.hpp>

namespace paradox
{
	Scene::Scene() :
	m_name("Untitled")
	{
		// Load scene?
	}

	Scene::~Scene()
	{
		// Unload scene?
	}

	void Scene::loadScene()
	{
		// Loop over all entities in the current scene file and create them?
	}

	void Scene::unloadScene()
	{
		// Loop over all entities in the current scene file and destroy them?
	}

	void Scene::setName(const std::string& name)
	{
		m_name = name;
	}

	std::string Scene::getName() const
	{
		return m_name;
	}
}