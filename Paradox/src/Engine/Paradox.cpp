#include <Engine/Paradox.hpp>

// SFML
#include <SFML/Window/Event.hpp>

namespace paradox
{
	const double dt = 1.0 / 60.0;

	Paradox::Paradox() :
	m_window(sf::VideoMode(800, 600), "Paradox")
	{
		// Temp
		m_window.setVerticalSyncEnabled(true);

		m_circle.setRadius(5.f);
		m_circle.setPosition(sf::Vector2f(100.f, 100.f));
		m_circle.setFillColor(sf::Color::Green);
	}

	Paradox::~Paradox()
	{
	}

	void Paradox::run()
	{
		while (m_window.isOpen())
		{
			pollEvents();
			update(dt);
			render();
		}
	}

	void Paradox::pollEvents()
	{
		sf::Event event;
		
		while (m_window.pollEvent(event))
		{
			// Exit application
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				m_window.close();
			}
		}
	}

	void Paradox::update(double dt)
	{
	}

	void Paradox::render()
	{
		m_window.clear();
		m_window.draw(m_circle);
		m_window.display();
	}
}