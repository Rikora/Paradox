#include <Engine/Paradox.hpp>

// SFML
#include <SFML/Window/Event.hpp>

// ImGUI
#include <imgui/imgui.h>
#include <imgui/imgui_dock.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	const double dt = 1.0 / 60.0;

	Paradox::Paradox() :
	m_window(sf::VideoMode(800, 600), "Paradox")
	{
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

			// Exit application
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
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