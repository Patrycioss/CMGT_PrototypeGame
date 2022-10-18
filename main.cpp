#include <iostream>
#include "SFMLPE/SFMLPE.hpp"
#include "TestGame.hpp"

int main() 
{
	TestGame game;
	game.Run(1920,1080,"Ha", "resources");
	return 0;
}


