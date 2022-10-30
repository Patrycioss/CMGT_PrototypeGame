#include "MainMenu.hpp"
#include "../ScoreManager.hpp"
#include "SFML/Window/Event.hpp"
#include "../CMGT_PrototypeGame.hpp"


MainMenu::MainMenu(CMGT_PrototypeGame& game) 
	: SFMLPE::Scene("MainMenu"), game_(game){}
	
	
void MainMenu::Start()
{
	background_ = std::make_unique<SFMLPE::Sprite>("background.png", sf::Vector2f{0,0});
	AddChild(background_.get());

	/////////////////////////////////////////////////////////////////////////////////////////////
	
	continueButton_ = std::make_unique<NewButton>(sf::Vector2f{150,210}, sf::Vector2f{300,100});
	
	continueButton_->rectShape().setFillColor(sf::Color(169,169,169));
	continueButton_->rectShape().setOutlineColor(sf::Color(105, 105, 105));
	continueButton_->rectShape().setOutlineThickness(10);
	
	continueButton_->text().setString("Start");
	continueButton_->text().setCharacterSize(50);
	continueButton_->text().setPosition(sf::Vector2f{continueButton_->position().x + 80, continueButton_->position().y + 20});

	continueButton_->SetPointerEnterAction([&](){  
		continueButton_->rectShape().setFillColor(sf::Color(169, 169, 169));
	});

	continueButton_->SetPointerExitAction([&](){ 	
		continueButton_->rectShape().setFillColor(sf::Color(169,169,169));
	});

	continueButton_->SetClickAction([this]() {
//		game_.SwapScene(Scenes::Arena);
	});

	AddChild(continueButton_.get());

	/////////////////////////////////////////////////////////////////////////////////////////////

	startNewButton_ = std::make_unique<NewButton>(sf::Vector2f{150,365}, sf::Vector2f{300,100});

	startNewButton_->rectShape().setFillColor(sf::Color::Green);
	startNewButton_->rectShape().setOutlineColor(sf::Color(0, 100, 0));
	startNewButton_->rectShape().setOutlineThickness(10);

	startNewButton_->text().setString("Start New");
	startNewButton_->text().setCharacterSize(50);
	startNewButton_->text().setPosition(sf::Vector2f{startNewButton_->position().x + 35, startNewButton_->position().y + 20});

	startNewButton_->SetPointerEnterAction([&]() {
		startNewButton_->rectShape().setFillColor(sf::Color(144, 238, 144));
	});

	startNewButton_->SetPointerExitAction([&]() {
		startNewButton_->rectShape().setFillColor(sf::Color::Green);
	});

	startNewButton_->SetClickAction([this]() {
		game_.SwapScene(Scenes::Selection);
	});

	AddChild(startNewButton_.get());
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	exitButton_ = std::make_unique<NewButton>(sf::Vector2f{150,520}, sf::Vector2f{300,100});

	exitButton_->rectShape().setFillColor(sf::Color::Red);
	exitButton_->rectShape().setOutlineColor(sf::Color(100, 0, 0));
	exitButton_->rectShape().setOutlineThickness(10);
	
	exitButton_->text().setString("Exit");
	exitButton_->text().setCharacterSize(50);
	exitButton_->text().setPosition(sf::Vector2f{exitButton_->position().x + 100, exitButton_->position().y + 20});

	exitButton_->SetPointerEnterAction([&]() {
		exitButton_->rectShape().setFillColor(sf::Color(255,204,203));
	});

	exitButton_->SetPointerExitAction([&]() { 
		exitButton_->rectShape().setFillColor(sf::Color::Red); 
	});

	exitButton_->SetClickAction([&]() {
		SFMLPE::Game::Stop();
	});

	AddChild(exitButton_.get());
	
	/////////////////////////////////////////////////////////////////////////////////////////////

	scoreViewer_ = std::make_unique<ScoreViewer>(sf::Vector2f{924,200});
	AddChild(scoreViewer_.get());

	SFMLPE::GameObject::Start();
}


