#include <iostream>
#include <random>
#include "../SFMLPE/SFMLPE.hpp"
#include "CMGT_PrototypeGame.hpp"

struct WindowNamePicker
{
	static const int amount = 5;
	
	const char* names[amount]{
		"Brought to you by ÉHâ─ ]├ÉUHëσHâ∞ Hï♣±%☻",
		"Brought to you by Chthonic Metal Games Tribe Company!",
		"Brought to you by three hamsters in a trenchcoat!",
		"AAAAAAHHHHHHH",
		":)     :|      :(      :'("
	};
	
	
	const char* GetName(const unsigned int& index = -1)
	{
		if (index == -1)
		{
			std::random_device rd{};
			std::mt19937 mt{rd()};
			std::uniform_int_distribution dist{0,amount-1};
			
			//printf(names[5]);
			
			return names[dist(mt)];
		}
		else if (index < 5) return names[index];
		
		else return "Nope";
	};
};

int main()
{
	CMGT_PrototypeGame game;
	game.Run(1300,800,WindowNamePicker().GetName(), "CMGT_PrototypeGame/Resources");
	return 0;
}



