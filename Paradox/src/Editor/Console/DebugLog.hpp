#pragma once

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	// Singleton instance
	class DebugLog
	{
	private:
		DebugLog() = default;
		~DebugLog() = default;
		DebugLog(const DebugLog&) {}
		DebugLog& operator = (const DebugLog&) {}
		DebugLog(const DebugLog&&) {}
		DebugLog& operator = (const DebugLog&&) {}

	public:
		void log(const char* fmt, ...) IM_FMTARGS(2);
		void draw();
		static DebugLog* getInstance();

	private:
		void clear();

		ImGuiTextBuffer m_buffer;
		ImVector<int> m_lineOffsets;
		bool m_scrollToBottom;
	};
}