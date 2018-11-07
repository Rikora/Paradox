#pragma once

// ImGUI
#include <imgui/imgui.h>

namespace paradox
{
	// Make this class a singleton instead?
	class DebugLog
	{
	public:
		static void log(const char* fmt, ...) IM_FMTARGS(2);
		static void draw();

	private:
		static void clear();

		static ImGuiTextBuffer m_buffer;
		static ImVector<int> m_lineOffsets;
		static bool m_scrollToBottom;
	};
}