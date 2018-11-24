#pragma once

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	class ToolMenu final : public Menu
	{
	public:
		~ToolMenu() = default;

		void update() override;
		void draw() override;
	};
}