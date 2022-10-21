#pragma once
#include "../../SFMLPE/SFMLPE.hpp"

class MainMenu : public SFMLPE::Scene
{
private:
	SFMLPE::AnimationSprite background_;
	
public:
	MainMenu();
	
	void Update() override;

};


