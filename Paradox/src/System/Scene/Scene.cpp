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
		// Add a basic entity for test
	/*	auto entity = m_entities.create();
		auto shape = std::make_unique<sf::CircleShape>(5.f);
		shape->setFillColor(sf::Color::Green);
		m_entities.assign<ShapeRenderer>(entity, std::move(shape));
		m_entities.assign<Transform>(entity, sf::Vector2f(200.f, 200.f), sf::Vector2f(1.f, 1.f), 0.f);*/
	}

	Scene::~Scene()
	{
		m_transformSystem.reset();
		m_renderSystem.reset();
	}

	void Scene::loadScene(const std::string& path)
	{
		// Cache the path for future need?
		json input;
		std::ifstream handle;
		std::ios_base::iostate exceptionMask = handle.exceptions() | std::ios::failbit;
		handle.exceptions(exceptionMask);

		try
		{
			handle.open(path);
			handle >> input;
			handle.close();
		}
		catch (const std::ios_base::failure& e)
		{
			std::cerr << "Error: Failed reading " << path << " -> " << std::strerror(errno) << std::endl; // TODO: log to game console
		}

		if (!input.empty())
		{
			// Load scene data
			for (unsigned i = 0; i < input["size"]; ++i)
			{
				// The entity will always have a transform?
				auto entity = m_entities.create();
				m_entities.assign<Transform>(entity, 
											 sf::Vector2f(input["transform"]["position"][0], input["transform"]["position"][1]), 
											 sf::Vector2f(input["transform"]["scale"][0], input["transform"]["scale"][1]),
											 input["transform"]["rotation"]);

				if (input["shapeRenderer"].is_object())
				{
					if (input["shapeRenderer"]["type"] == "Circle")
					{
						auto circle = std::make_unique<sf::CircleShape>(input["shapeRenderer"]["radius"].get<float>());
						circle->setFillColor(sf::Color(input["shapeRenderer"]["color"][0],
													   input["shapeRenderer"]["color"][1],
													   input["shapeRenderer"]["color"][2]));

						m_entities.assign<ShapeRenderer>(entity, std::move(circle));
					}

					// TODO: add case for rectangle
				}
			}	
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
			output["transform"]["position"] = { transform.position.x, transform.position.y };
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
				//else if (typeid(*shapeRenderer.shape.get()) == typeid(sf::RectangleShape))
				//{
				//	auto rect = dynamic_cast<sf::RectangleShape*>(shapeRenderer.shape.get());

				//	output["shapeRenderer"]["type"] = "Rectangle";	
				//	//
				//}
			}		
		}

		std::ofstream o("meta/untitled.scene"); // Hardcoded scene path 
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