#include "MainMenu.hpp"

MainMenu::MainMenu() : SFMLPE::Scene("main_menu")
	, background_(sf::Vector2f{0,0}, "background.png", 1,1,1)
{
	AddChild(&background_);
}

void MainMenu::Update() {
	GameObject::Update();
	background_.Animate();
}


