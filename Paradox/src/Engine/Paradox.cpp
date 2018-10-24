#include <Engine/Paradox.hpp>

// C++
#include <fstream>
#include <iomanip>
#include <iostream>

// SFML
#include <SFML/Window/Event.hpp>

// ImGUI
#include <imgui/imgui.h>
#include <imgui/imgui_dock.h>
#include <imgui/imgui-SFML.h>

// Json
#include <json/json.hpp>

using namespace nlohmann;

namespace paradox
{
	const double dt = 1.0 / 60.0;

	Paradox::Paradox()
	{
		// Get settings for the current instance of the engine
		json data;
		std::ifstream handle;
		std::ios_base::iostate exceptionMask = handle.exceptions() | std::ios::failbit;
		handle.exceptions(exceptionMask);

		try
		{
			handle.open("meta/paradox.ini");
			handle >> data;
			handle.close();
		}
		catch (const std::ios_base::failure& e)
		{
			std::cerr << "Error: Failed reading paradox.ini -> " << std::strerror(errno) << std::endl; // TODO: LOG to game console
		}

		if (!data.empty())
		{
			m_window.setPosition(sf::Vector2i(data["winPos"][0], data["winPos"][1]));
			m_window.create(sf::VideoMode(data["winSize"][0], data["winSize"][1]), "Paradox");
		}
		else
		{
			// Create window with default settings
			m_window.create(sf::VideoMode(800, 600), "Paradox");
		}

		// Temp
		m_window.setVerticalSyncEnabled(true);

		// Init GUI
		ImGui::SFML::Init(m_window);
		ImGui::InitDock();

		m_circle.setRadius(5.f);
		m_circle.setPosition(sf::Vector2f(100.f, 100.f));
		m_circle.setFillColor(sf::Color::Green);
	}

	Paradox::~Paradox()
	{
		ImGui::SFML::Shutdown();
	}

	void Paradox::run()
	{
		sf::Clock clock;

		while (m_window.isOpen())
		{
			pollEvents();
			update(clock.restart());
			render();
		}
	}

	void Paradox::pollEvents()
	{
		sf::Event event;
		
		while (m_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			// Resize
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect viewArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
				m_window.setView(sf::View(viewArea));
			}

			// Exit application
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				// Dump settings file
				json settings;
				settings["winPos"] = { m_window.getPosition().x, m_window.getPosition().y };
				settings["winSize"] = { m_window.getSize().x, m_window.getSize().y };

				std::ofstream o("meta/paradox.ini");
				o << std::setw(4) << settings << std::endl;
				o.close();

				m_window.close();
			}
		}
	}

	void Paradox::update(sf::Time dt)
	{
		// Update GUI
		ImGui::SFML::Update(m_window, dt);

		// Test dock layout
		if (ImGui::Begin("Dock Demo"))
		{
			ImGui::BeginDockspace();

			if (ImGui::BeginDock("Dock 1")) {
				ImGui::Text("I'm Wubugui!");
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Dock 2")) {
				ImGui::Text("I'm BentleyBlanks!");
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Dock 3")) {
				ImGui::Text("I'm LonelyWaiting!");
			}
			ImGui::EndDock();

			ImGui::EndDockspace();
		}
		ImGui::End();
	}

	void Paradox::render()
	{
		m_window.clear();
		m_window.draw(m_circle);

		// Render GUI
		ImGui::SFML::Render(m_window);

		m_window.display();
	}
}