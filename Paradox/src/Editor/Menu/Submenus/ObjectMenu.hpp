#pragma once

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	class ObjectMenu final : public Menu
	{
	public:
		~ObjectMenu() = default;

		void update() override;
		void draw() override;
	};
}