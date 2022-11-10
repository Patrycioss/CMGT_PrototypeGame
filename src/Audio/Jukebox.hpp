#pragma once

#include <map>
#include "SFML/Audio.hpp"

enum class Mode
{
	Idle,
	Battle
};

struct Track
{
	std::string path;
	float volume;
};

class Jukebox
{
	friend class CMGT_PrototypeGame;
	
private:
	Jukebox();
	
	static Track idleTracks_[3];
	static Track battleTracks_[3];
	
	static std::unordered_map<Mode, std::pair<Track*, sf::Time>> storedSongs_;
	
	static sf::Music currentMusic_;
	
	static Mode currentMode_;
	static Track* currentTrack_;
	
	static void Start();
	static void Update();
	
public:
	
	sf::Sound buttonClick;
	sf::Sound exit;
	
	static void Play(const Mode& mode);

	static Jukebox& get();
	static Track& GetRandomTrack(const Mode& mode);

};

