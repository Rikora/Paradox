#pragma once

namespace paradox
{
	// Brief sketch of abstract base class for docks
	class Dock
	{
	public:
		virtual ~Dock() {}

		virtual void update() = 0;
		virtual void draw() = 0;
	};
}