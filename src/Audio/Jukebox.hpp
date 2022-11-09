#pragma once
#include "SFML/Audio.hpp"

class Jukebox
{
private:
	Jukebox();
public:
	
	sf::Sound buttonClick;
	sf::Sound exit;

	static Jukebox& get();
};

