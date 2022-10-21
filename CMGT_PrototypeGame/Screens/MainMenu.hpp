#pragma once
#include "../../SFMLPE/SFMLPE.hpp"

class MainMenu : public SFMLPE::Scene
{
private:
	SFMLPE::AnimationSprite* background_;
	SFMLPE::AnimationSprite* startButton_;
	
	bool overStart_ = false;
	
public:
	void Start() override;
	void Update() override;
	MainMenu();
	~MainMenu();
};


