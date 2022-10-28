#pragma once
#include "../SFMLPE/SFMLPE.hpp"
#include "AnimationTest.hpp"
#include "../test_example/TestSprite.hpp"
#include "Screens/MainMenu.hpp"


class CMGT_PrototypeGame : public SFMLPE::Game // NOLINT(cppcoreguidelines-pro-type-member-init)
{
private:
	std::unique_ptr<MainMenu> mainMenu;
	SFMLPE::Scene scene{"test"};
	
	
protected:
	void Start() override;
	void Update() override;
	void End() override;
};