#include <filesystem>
#include "MainMenu.hpp"
#include "SFML/Window/Event.hpp"
#include "../CMGT_PrototypeGame.hpp"
#include "effolkronium/random.hpp"
#include "../Audio/Jukebox.hpp"
#include "../Utility/Timers/TimerManager.hpp"


MainMenu::MainMenu(CMGT_PrototypeGame& game) 
	: Scene("MainMenu"), game_(game){}
	
	
void MainMenu::Start()
{
	Jukebox::Play(Mode::Idle);
	
	background_ = std::make_unique<Sprite>("background.png", sf::Vector2f{0,0});
	AddChild(background_.get());

	/////////////////////////////////////////////////////////////////////////////////////////////
	
	continueButton_ = std::make_unique<Button>(sf::Vector2f{150,210}, sf::Vector2f{300,100});
	
	continueButton_->rectShape().setFillColor(sf::Color::Green);
	continueButton_->rectShape().setOutlineColor(sf::Color(0, 100, 0));
	continueButton_->rectShape().setOutlineThickness(10);
	
	continueButton_->text().setString("Continue");
	continueButton_->text().setCharacterSize(50);
	continueButton_->text().setPosition(sf::Vector2f{continueButton_->position().x + 45, continueButton_->position().y + 20});

	continueButton_->SetPointerEnterAction([&](){  
		continueButton_->rectShape().setFillColor(sf::Color(210, 248, 210));
	});

	continueButton_->SetPointerExitAction([&](){ 	
		continueButton_->rectShape().setFillColor(sf::Color::Green);
	});

	continueButton_->SetClickAction([this]() {
		dynamic_cast<Arena*>(game_.SwapScene(Scenes::Arena))
				->Continue(SaveLoader::Load("../user_data/latest_save.cmgt"));
	});
	
	if (!std::filesystem::exists("../user_data/latest_save.cmgt"))
	{
		continueButton_->rectShape().setFillColor(sf::Color{169,169,169});
		continueButton_->rectShape().setOutlineColor(sf::Color{123,123,123});
		continueButton_->Lock(true);
	}
	

	AddChild(continueButton_.get());

	/////////////////////////////////////////////////////////////////////////////////////////////

	startNewButton_ = std::make_unique<Button>(sf::Vector2f{150,365}, sf::Vector2f{300,100});

	startNewButton_->rectShape().setFillColor(sf::Color::Green);
	startNewButton_->rectShape().setOutlineColor(sf::Color(0, 100, 0));
	startNewButton_->rectShape().setOutlineThickness(10);

	startNewButton_->text().setString("Start New");
	startNewButton_->text().setCharacterSize(50);
	startNewButton_->text().setPosition(sf::Vector2f{startNewButton_->position().x + 35, startNewButton_->position().y + 20});

	startNewButton_->SetPointerEnterAction([&]() {
		startNewButton_->rectShape().setFillColor(sf::Color(210, 248, 210));
	});

	startNewButton_->SetPointerExitAction([&]() {
		startNewButton_->rectShape().setFillColor(sf::Color::Green);
	});

	startNewButton_->SetClickAction([this]() {
		game_.SwapScene(Scenes::Selection);
	});

	AddChild(startNewButton_.get());
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	exitButton_ = std::make_unique<Button>(sf::Vector2f{150,520}, sf::Vector2f{300,100});

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
		Jukebox::get().exit.play();
		
		TimerManager::AddTimer(Timer(sf::seconds(1), []()
		{
			Game::Stop();
		}));
	});

	AddChild(exitButton_.get());
	
	/////////////////////////////////////////////////////////////////////////////////////////////

	scoreViewer_ = std::make_unique<ScoreViewer>(sf::Vector2f{924,200});
	AddChild(scoreViewer_.get());

	GameObject::Start();
}