#pragma once
#include "Character.hpp"
#include "../NewButton.hpp"
#include "../../SFMLPE/SFMLPE.hpp"

class CMGT_PrototypeGame;

class Arena : public SFMLPE::Scene
{
private:
	bool playerTurn_ = false;
	
	Character player_;
	Character enemy_;

	std::unique_ptr<NewButton> attackButton_;
	std::unique_ptr<NewButton> prepareButton_;
	std::unique_ptr<NewButton> recoverButton_;
	std::unique_ptr<NewButton> castMagicButton_;
	
	CMGT_PrototypeGame& game_;
	
public:
	Arena(CMGT_PrototypeGame& game);
	

};
