#include <System/Scene/Scene.hpp>

// C++
#include <fstream>
#include <iomanip>
#include <iostream>

// SFML
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// Paradox
#include <System/Logic/TransformSystem.hpp>
#include <System/Logic/RenderSystem.hpp>
#include <System/Component/ShapeRenderer.hpp>
#include <System/Component/Transform.hpp>

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
		// Dump scene file
		json output;

		output["size"] = m_entities.alive();

		auto view = m_entities.view<Transform, ShapeRenderer>(); // More components will follow here...

		for (const auto& entity : view)
		{
			auto& transform = view.get<Transform>(entity);

			// The entity will always have a transform?
			output["transform"] = transform.position.x;
			output["transform"]["scale"] = { transform.scale.x, transform.scale.y };
			output["transform"]["rotation"] = transform.rotation;

			if (m_entities.has<ShapeRenderer>(entity))
			{
				auto& shapeRenderer = view.get<ShapeRenderer>(entity);

				auto fillColor = shapeRenderer.shape->getFillColor();
				output["shapeRenderer"]["color"] = { fillColor.r, fillColor.g, fillColor.b };

				if (typeid(*shapeRenderer.shape.get()) == typeid(sf::CircleShape))
				{
					auto circle = dynamic_cast<sf::CircleShape*>(shapeRenderer.shape.get());

					output["shapeRenderer"]["type"] = "Circle";
					output["shapeRenderer"]["radius"] = circle->getRadius();

				}
				else if (typeid(*shapeRenderer.shape.get()) == typeid(sf::RectangleShape))
				{
					auto rect = dynamic_cast<sf::RectangleShape*>(shapeRenderer.shape.get());

					output["shapeRenderer"]["type"] = "Rectangle";	
					//
				}
			}		
		}

		std::ofstream o("meta/untitled.scene");
		o << std::setw(4) << output << std::endl;
		o.close();
	}

	void Scene::unloadScene()
	{
		m_entities.destroy<Transform>();
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