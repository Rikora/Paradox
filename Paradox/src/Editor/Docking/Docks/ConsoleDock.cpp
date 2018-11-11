#include <Editor/Docking/Docks/ConsoleDock.hpp>

// Paradox
#include <Editor/Console/DebugLog.hpp>

namespace paradox
{
	void ConsoleDock::draw()
	{
		DebugLog::getInstance()->draw();
	}
}
