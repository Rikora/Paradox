#pragma once

// C++
#include <memory>

// SFML
#include <SFML/Graphics/Sprite.hpp>

namespace paradox
{
	struct SpriteRenderer
	{
		std::unique_ptr<sf::Sprite> sprite;
	};
}