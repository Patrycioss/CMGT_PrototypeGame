#pragma once
#include "SFMLPE/SFMLPE.hpp"
#include "TestSprite.hpp"

class TestGame : public SFMLPE::Game
{
private:
	float speed = 2;
	
	TestSprite* a;
	SFMLPE::Sprite* b;
	
protected:
	void Start() override;
	void Update() override;
	
public:
	TestGame();
};