#pragma once
#include "SFML/Audio.hpp"

class Jukebox
{
private:
	Jukebox();
	
	std::string idleTracks_[3];
	std::string fightTracks_[3];

public:
	
	sf::Sound buttonClick;
	sf::Sound exit;
	
	sf::Music music;

	static Jukebox& get();
};

