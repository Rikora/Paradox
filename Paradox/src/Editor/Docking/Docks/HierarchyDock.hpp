#pragma once

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace paradox
{
	class HierarchyDock final : public Dock
	{
	public:
		HierarchyDock();
		~HierarchyDock() = default;

		void update() override;
		void draw() override;

	private:
		bool m_selected;
	};
}