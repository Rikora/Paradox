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

#include <System/Component/Property.hpp>
#include <System/Component/SpriteRenderer.hpp>
#include <System/Component/ShapeRenderer.hpp>
#include <System/Component/Transform.hpp>

// Json
#include <json/json.hpp>

using namespace nlohmann;

namespace paradox
{
	Scene::Scene() :
	m_name("untitled.scene"),
	m_transformSystem(std::make_unique<TransformSystem>()),
	m_renderSystem(std::make_unique<RenderSystem>())
	{
		// Add a basic entity for test
		/*auto entity = m_entities.create();
		auto shape = std::make_unique<sf::CircleShape>(5.f);
		shape->setFillColor(sf::Color::Green);
		m_entities.assign<Property>(entity, "gameObject");
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
			// Set current scene name
			std::string tempPath = path;
			std::replace(tempPath.begin(), tempPath.end(), '\\', '/');
			const auto found = tempPath.find_last_of("/");
			const auto name = tempPath.substr(found + 1);

			// Make sure we don't append scene data to the current scene
			if (m_name != name)
			{
				unloadScene();
				m_name = name;
			}

			// Load scene data
			for (unsigned i = 0; i < input["size"]; ++i)
			{
				auto entity = m_entities.create();

				// Property
				m_entities.assign<Property>(entity, input["scene"][i]["property"]["name"].get<std::string>());

				// Transform
				m_entities.assign<Transform>(
					entity, 
					sf::Vector2f(input["scene"][i]["transform"]["position"][0], input["scene"][i]["transform"]["position"][1]),
					sf::Vector2f(input["scene"][i]["transform"]["scale"][0], input["scene"][i]["transform"]["scale"][1]),
					input["scene"][i]["transform"]["rotation"]);

				// ShapeRenderer
				if (input["scene"][i]["spriteRenderer"].is_object())
				{
					auto sprite = std::make_unique<sf::Sprite>(); // TODO: add texture here

					sprite->setColor(
							sf::Color(input["scene"][i]["spriteRenderer"]["color"][0],
							input["scene"][i]["spriteRenderer"]["color"][1],
							input["scene"][i]["spriteRenderer"]["color"][2]));

					// Prevent transform glitch when loading a scene
					auto transform = m_entities.get<Transform>(entity);
					sprite->setPosition(transform.position);
					sprite->setScale(transform.scale);
					sprite->setRotation(transform.rotation);

					m_entities.assign<SpriteRenderer>(entity, std::move(sprite));
				}
				else if (input["scene"][i]["shapeRenderer"].is_object())
				{
					if (input["scene"][i]["shapeRenderer"]["type"] == "Circle")
					{
						auto circle = std::make_unique<sf::CircleShape>(input["scene"][i]["shapeRenderer"]["radius"].get<float>());

						circle->setFillColor(
							sf::Color(input["scene"][i]["shapeRenderer"]["color"][0],
							input["scene"][i]["shapeRenderer"]["color"][1],
							input["scene"][i]["shapeRenderer"]["color"][2]));

						// Prevent transform glitch when loading a scene
						auto transform = m_entities.get<Transform>(entity);
						circle->setPosition(transform.position);
						circle->setScale(transform.scale);
						circle->setRotation(transform.rotation);

						m_entities.assign<ShapeRenderer>(entity, std::move(circle));
					}
				}
			}	
		}
	}

	void Scene::saveScene()
	{
		// Dump scene fil
		json output;

		unsigned index = 0;
		output["size"] = m_entities.alive();

		m_entities.each([this, &index, &output](const auto& entity) 
		{
			// Property
			auto& property = m_entities.get<Property>(entity);

			output["scene"][index]["property"]["name"] = property.name;

			// Transform
			auto& transform = m_entities.get<Transform>(entity);

			output["scene"][index]["transform"]["position"] = { transform.position.x, transform.position.y };
			output["scene"][index]["transform"]["scale"] = { transform.scale.x, transform.scale.y };
			output["scene"][index]["transform"]["rotation"] = transform.rotation;

			// Shapes
			if (m_entities.has<SpriteRenderer>(entity))
			{
				auto& spriteRenderer = m_entities.get<SpriteRenderer>(entity);

				auto color = spriteRenderer.sprite->getColor();
				output["scene"][index]["spriteRenderer"]["color"] = { color.r, color.g, color.b };
			}
			else if (m_entities.has<ShapeRenderer>(entity))
			{
				auto& shapeRenderer = m_entities.get<ShapeRenderer>(entity);

				auto fillColor = shapeRenderer.shape->getFillColor();
				output["scene"][index]["shapeRenderer"]["color"] = { fillColor.r, fillColor.g, fillColor.b };

				if (typeid(*shapeRenderer.shape.get()) == typeid(sf::CircleShape))
				{
					auto circle = dynamic_cast<sf::CircleShape*>(shapeRenderer.shape.get());

					output["scene"][index]["shapeRenderer"]["type"] = "Circle";
					output["scene"][index]["shapeRenderer"]["radius"] = circle->getRadius();
				}
			}

			index++;

		});

		std::ofstream o("meta/" + m_name); // Hardcoded meta folder
		o << std::setw(4) << output << std::endl;
		o.close();
	}

	void Scene::unloadScene()
	{
		m_entities.destroy<Property>();
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