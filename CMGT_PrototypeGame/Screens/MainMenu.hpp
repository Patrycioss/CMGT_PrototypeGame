#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "../IO/Buttons/Button.hpp"
#include "../IO/Buttons/StartButton.hpp"
#include "../IO/Buttons/ExitButton.hpp"
#include "../MainMenu/ScoreViewer.hpp"

class MainMenu : public SFMLPE::Scene
{
private:
	std::unique_ptr<SFMLPE::Sprite> background_;
//	std::unique_ptr<SFMLPE::AnimationSprite> waves_;
	std::unique_ptr<StartButton> startButton_;
	std::unique_ptr<ExitButton> exitButton_;
	std::unique_ptr<ScoreViewer> scoreViewer_;
	
	bool overStart_ = false;
	
public:
	void Start() override;
	void Update() override;
	MainMenu();
};


