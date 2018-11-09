#pragma once

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	class FileMenu final : public Menu
	{
	public:
		~FileMenu() = default;

		//virtual void pollEvents(const sf::Event& event) override;
		//virtual void update() override;
		virtual void draw() override;

	private:
		void newScene();
		void openScene();
		void saveScene();
		void saveSceneAs();
		void exit();
	};
}