#pragma once
#include "Game.hpp"
#include "../EventSystem/EventHandler.hpp"
#include "../Drawing/Sprite.hpp"

namespace SFMLPE
{
	class MyGame : public Game
	{
	private:
		void Start() override;
		void Update() override;
		
		EventHandler* eventHandler;
		int* times;
	};
}




