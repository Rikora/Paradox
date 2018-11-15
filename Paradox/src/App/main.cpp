// Test for sol
#include <Engine/Paradox.hpp>

//#include <sol/sol.hpp>
//#include <cassert>

//#ifdef _WIN32
//	#include <Windows.h>
//#endif
//
//#ifdef _WIN32
//INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
//#else
int main(int args, char* argv[])
//#endif
{
	//std::cout << "=== opening a state ===" << std::endl;

	//sol::state lua;

	//// open some common libraries
	//lua.open_libraries(sol::lib::base, sol::lib::package);
	//lua.script("print('bark bark bark!')");

	//std::cout << std::endl;

	paradox::Paradox engine;
	engine.run();

	return 0;
}