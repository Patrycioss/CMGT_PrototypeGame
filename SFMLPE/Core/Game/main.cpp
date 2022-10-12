#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "MyGame.hpp"


int main() 
{
	SFMLPE::MyGame game = SFMLPE::MyGame();
	game.Run(700,700,"Ha","resources");
	return 0;
}


