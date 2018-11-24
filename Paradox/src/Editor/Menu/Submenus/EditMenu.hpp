#pragma once

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	class EditMenu final : public Menu
	{
	public:
		~EditMenu() = default;

		void update() override;
		void draw() override;
	};
}