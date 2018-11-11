#pragma once

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace paradox
{
	class ConsoleDock final : public Dock
	{
	public:
		~ConsoleDock() = default;

		virtual void draw() override;
	};
}