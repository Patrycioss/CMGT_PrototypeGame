#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "../MainMenu/ScoreViewer.hpp"

class CMGT_PrototypeGame;

class MainMenu : public SFP::Scene
{
private:
	std::unique_ptr<SFP::Sprite> background_;
	std::unique_ptr<NewButton> continueButton_;
	std::unique_ptr<NewButton> startNewButton_;
	std::unique_ptr<NewButton> exitButton_;
	std::unique_ptr<ScoreViewer> scoreViewer_;
	
	bool overStart_ = false;
	CMGT_PrototypeGame& game_;
	
	sf::Music music_;
	sf::Clock clock_;
	sf::Clock loopSlower_;
	
	const char* musicFiles_[3] = {
			"music/scary_terraria.mp3",
			"music/mario_flintstones.mp3",
			"music/athletic_theme.mp3"
	};
	
public:
	void Start() override;
	explicit MainMenu(CMGT_PrototypeGame& game);
};


