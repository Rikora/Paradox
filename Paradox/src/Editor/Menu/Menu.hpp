#pragma once

namespace paradox
{
	// Menu base class
	class Menu
	{
	public:
		virtual ~Menu() {}

		virtual void pollEvents() = 0;
		virtual void draw() = 0;
	};
}