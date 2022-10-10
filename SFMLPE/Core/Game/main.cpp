#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MyGame.hpp"


int main() 
{
	SFMLPE::MyGame game = SFMLPE::MyGame();
	game.Run(500,500,"Ha","resources");
	return 0;
}


