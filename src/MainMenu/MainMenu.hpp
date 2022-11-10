#pragma once
#include "../Engine/Scene.hpp"
#include "SFML/Audio/Music.hpp"
#include "../Engine/Sprite.hpp"
#include "../Engine/Button.hpp"
#include "ScoreViewer.hpp"

class CMGT_PrototypeGame;

class MainMenu : public Scene
{
private:
	std::unique_ptr<Sprite> background_;
	std::unique_ptr<Button> continueButton_;
	std::unique_ptr<Button> startNewButton_;
	std::unique_ptr<Button> exitButton_;
	std::unique_ptr<ScoreViewer> scoreViewer_;
	
	bool overStart_ = false;
	CMGT_PrototypeGame& game_;
	
	const char* musicFiles_[3] = {
			"music/scary_terraria.mp3",
			"music/mario_flintstones.mp3",
			"music/athletic_theme.mp3"
	};
	
public:
	void Start() override;
	explicit MainMenu(CMGT_PrototypeGame& game);
};


