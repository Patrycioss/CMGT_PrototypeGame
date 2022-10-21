#include "MainMenu.hpp"

MainMenu::MainMenu() : SFMLPE::Scene("main_menu"){}

void MainMenu::Start()
{
	background_ = new SFMLPE::AnimationSprite(sf::Vector2f{0,0}, "background.png", 3, 1 ,3);
	background_->SetCycle(0,3,500);
	AddChild(background_);

	startButton_ = new SFMLPE::AnimationSprite(sf::Vector2f{150,200}, "startButton.png", 4, 1 ,4);
	startButton_->SetCycle(0,3,400);
	AddChild(startButton_);
	
	
}

void MainMenu::Update() {
	GameObject::Update();
	background_->Animate();
	startButton_->Animate();
	
//	printf("X: %f, Y: %f \n", startButton_->position().x, startButton_->position().y);
////	printf("SizeX: %f, SizeY: %f \n", )
//	printf("MouseX: %f, MouseY: %f \n", mousePosition.x, mousePosition.y);
//	printf("?: %s \n", (startButton_->PointOver(sf::Vector2f(160, 210))? "Ja" : "Nee"));
	
	
	if (startButton_->PointOver(mousePosition))
	{
		printf("Ja");
		if (!overStart_)
		{
			overStart_ = true;
			
			startButton_->SetCycle(3,1, 400);
		}
	}
	else if (overStart_)
	{
		startButton_->SetCycle(0,3,400);
		overStart_ = false;
	}
}

MainMenu::~MainMenu() 
{
	delete background_;
	delete startButton_;
}




