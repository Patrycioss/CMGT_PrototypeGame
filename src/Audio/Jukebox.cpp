#include "Jukebox.hpp"
#include "../Engine/ResourceManager.hpp"

Jukebox& Jukebox::get() {
	static Jukebox jukebox;
	return jukebox;
}

Jukebox::Jukebox() {
	exit.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/exit.wav"));
	buttonClick.setBuffer(*ResourceManager::LoadSoundBuffer("sounds/click.wav"));
}
