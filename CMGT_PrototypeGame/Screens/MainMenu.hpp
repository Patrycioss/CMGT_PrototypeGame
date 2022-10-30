#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "../Deprecated/Button.hpp"
#include "../Deprecated/StartButton.hpp"
#include "../Deprecated/ExitButton.hpp"
#include "../MainMenu/ScoreViewer.hpp"

class CMGT_PrototypeGame;

class MainMenu : public SFMLPE::Scene
{
private:
	std::unique_ptr<SFMLPE::Sprite> background_;
	std::unique_ptr<NewButton> continueButton_;
	std::unique_ptr<NewButton> startNewButton_;
	std::unique_ptr<NewButton> exitButton_;
	std::unique_ptr<ScoreViewer> scoreViewer_;
	
	bool overStart_ = false;
	CMGT_PrototypeGame& game_;
	
public:
	void Start() override;
	explicit MainMenu(CMGT_PrototypeGame& game);
};


