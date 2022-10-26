#include "MainMenu.hpp"
#include "../Data/ScoreManager.hpp"
#include "SFML/Window/Event.hpp"


MainMenu::MainMenu() : SFMLPE::Scene("main_menu"){}

void MainMenu::Start()
{
	background_ = std::make_unique<SFMLPE::Sprite>("background.png", sf::Vector2f{0,0});
	AddChild(background_.get());

	startButton_ = std::make_unique<StartButton>(sf::Vector2f{150,200});
	AddChild(startButton_.get());	
	
	exitButton_ = std::make_unique<ExitButton>(sf::Vector2f{150, 400});
	AddChild(exitButton_.get());
	
	scoreViewer_ = std::make_unique<ScoreViewer>(sf::Vector2f{924,200});
	AddChild(scoreViewer_.get());

	waves_ = std::make_unique<SFMLPE::AnimationSprite>(sf::Vector2f{0,0}, "waves.png", 3, 1 ,3);
	waves_->SetCycle(0,3,500);
	AddChild(waves_.get());


//	ScoreManager::LoadScores();
//	Score data = ScoreManager::score("Test");
//	printf("Name: %s, DPS: %d, SLAIN: %d \n", data.name.c_str(), data.damageDone, data.enemiesSlain);
//	
//	Score hoi{"Hoi", 1, 2};
//	ScoreManager::StoreScore(hoi.name, hoi);
//	
//	const Score& hoiData = ScoreManager::score("Hoi");
//	
////	printf("Stored: N: %s, DPS: %d, SLAIN: %d \n", hoiData.name.c_str(), hoiData.damageDone, hoiData.enemiesSlain);
//
//	ScoreManager::SortScores();
//	
//	ScoreManager::SaveScores();
}

void MainMenu::Update() 
{
	GameObject::Update();
	waves_->Animate();
}