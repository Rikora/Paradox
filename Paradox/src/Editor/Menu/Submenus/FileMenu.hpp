#pragma once

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	class FileMenu final : public Menu
	{
	public:
		FileMenu();
		~FileMenu() = default;

		void pollEvents() override;
		void draw() override;

	private:
		void newScene();
		void openScene();
		void saveScene();
		void saveSceneAs();
		void exit();
	};
}