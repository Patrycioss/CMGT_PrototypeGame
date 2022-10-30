#pragma once
#include "../SFMLPE/SFMLPE.hpp"
#include "NewButton.hpp"

class CMGT_PrototypeGame;

class Selection : public SFMLPE::Scene
{   
private:
	sf::RectangleShape background_;
	
	std::unique_ptr<SFMLPE::AnimationSprite> choices_[3];
	std::unique_ptr<NewButton> choiceButtons_[3];
	
	CMGT_PrototypeGame& game_;
	
	
public:
	Selection(CMGT_PrototypeGame& game);
	
	void Update() override;
	void Render(sf::RenderWindow& window) override;
};