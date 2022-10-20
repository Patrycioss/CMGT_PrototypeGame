#pragma once
#include "../SFMLPE/SFMLPE.hpp"
#include "AnimationTest.hpp"
#include "../test_example/TestSprite.hpp"


class CMGT_PrototypeGame : public SFMLPE::Game // NOLINT(cppcoreguidelines-pro-type-member-init)
{
private:
	SFMLPE::Scene fight_screen = SFMLPE::Scene("fight_screen");
	SFMLPE::Scene main_menu = SFMLPE::Scene("main_menu");
	
	AnimationTest* animationTest;
	TestSprite* testSprite;
	AnimationTest* animationTest2;
	
	
protected:
	void Start() override;
	void Update() override;
	void End() override;
};