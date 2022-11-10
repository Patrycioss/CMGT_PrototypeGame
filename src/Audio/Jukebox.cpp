#include "Jukebox.hpp"
#include "../Engine/ResourceManager.hpp"
#include "effolkronium/random.hpp"

Track Jukebox::idleTracks_[3]
{
	{"music/idle/1.ogg", 1},
	{"music/idle/2.ogg", 1},
	{"music/idle/3.ogg", 1}
};

Track Jukebox::battleTracks_[3]
{		
	{"music/battle/1.ogg", 1},
	{"music/battle/2.ogg", 1},
	{"music/battle/3.ogg", 1}
};

std::unordered_map<Mode, std::pair<Track*, sf::Time>> Jukebox::storedSongs_;

Mode Jukebox::currentMode_;
Track* Jukebox::currentTrack_;
sf::Music Jukebox::currentMusic_;


Jukebox& Jukebox::get() {
	static Jukebox jukebox;
	return jukebox;
}

Jukebox::Jukebox()
{
	exit.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/exit.wav"));
	exit.setVolume(5);
	buttonClick.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/click.wav"));
	buttonClick.setVolume(10);
	Start();
}

void Jukebox::Start() 
{
	currentMusic_.setLoop(false);
}

void Jukebox::Play(const Mode& mode) 
{
	if (currentMode_ == mode)  return;
	
	currentMusic_.pause();
	
	if (currentTrack_ != nullptr)
		storedSongs_[currentMode_] = std::pair(currentTrack_, currentMusic_.getPlayingOffset());
	
	currentMode_ = mode;
	
	auto it = storedSongs_.find(mode);
	
	if (it != storedSongs_.end() && currentTrack_ != nullptr)
	{
		currentTrack_ = it->second.first;
		currentMusic_.openFromFile(currentTrack_->path);
		currentMusic_.setVolume(currentTrack_->volume);
		currentMusic_.play();
		currentMusic_.setPlayingOffset(it->second.second);
	}
	else
	{
		currentMusic_.stop();
		Track& track = GetRandomTrack(mode);
		currentTrack_ = &track;
		currentMusic_.openFromFile(track.path);
		currentMusic_.setVolume(track.volume);
		currentMusic_.play();
	}

}

void Jukebox::Update() 
{
	if (currentMusic_.getStatus() == sf::SoundSource::Stopped)
	{
		Track& track = GetRandomTrack(currentMode_);

		currentTrack_ = &track;
		currentMusic_.openFromFile(track.path);
		currentMusic_.setVolume(track.volume);
		currentMusic_.setLoop(false);
		currentMusic_.play();
	}
}   

Track& Jukebox::GetRandomTrack(const Mode& mode)
{
	const int i = effolkronium::random_static::get(0,2);
	
	switch (mode)
	{
		case Mode::Idle:
			return idleTracks_[i]; 
		case Mode::Battle:
			return battleTracks_[i];
			
	}

	throw std::invalid_argument("Shouldn't happen in GetRandomTrack");
}
