#include <System/Scene/Scene.hpp>

// C++
#include <fstream>
#include <iomanip>
#include <iostream>

// SFML
//#include <SFML/Graphics/RenderTarget.hpp>

// Paradox
#include <System/Logic/TransformSystem.hpp>
#include <System/Logic/RenderSystem.hpp>

// Json
#include <json/json.hpp>

using namespace nlohmann;

namespace paradox
{
	Scene::Scene() :
	m_name("Untitled"),
	m_transformSystem(std::make_unique<TransformSystem>()),
	m_renderSystem(std::make_unique<RenderSystem>())
	{
	}

	Scene::~Scene()
	{
		m_transformSystem.reset();
		m_renderSystem.reset();
	}

	void Scene::loadScene(const std::string& path)
	{
		// Cache the path for future need?
		json data;
		std::ifstream handle;
		std::ios_base::iostate exceptionMask = handle.exceptions() | std::ios::failbit;
		handle.exceptions(exceptionMask);

		try
		{
			handle.open(path);
			handle >> data;
			handle.close();
		}
		catch (const std::ios_base::failure& e)
		{
			std::cerr << "Error: Failed reading " << path << " -> " << std::strerror(errno) << std::endl; // TODO: log to game console
		}

		if (!data.empty())
		{
			// TODO: create entities from the scene data	
		}
	}

	void Scene::saveScene()
	{
		// Any ability in entt to serialize entities directly?

		// TODO: save all the scene data to disk
	}

	void Scene::unloadScene()
	{
		// Loop over all entities in the current scene file and destroy them?
	}

	void Scene::update()
	{
		m_transformSystem->update(m_entities);
	}

	void Scene::draw(sf::RenderTarget& target)
	{
		m_renderSystem->update(m_entities, target);
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