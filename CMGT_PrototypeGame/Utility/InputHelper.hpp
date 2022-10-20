#pragma once
#include "SFML/System/Vector2.hpp"

class InputHelper {
public:
	static sf::Vector2f get_wasd_direction();
	static sf::Vector2f get_arrowKeys_direction();
};

