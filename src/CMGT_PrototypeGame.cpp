#include "CMGT_PrototypeGame.hpp"
#include "Utility/Timers/TimerManager.hpp"
#include "Utility/Tweening/TweenManager.hpp"
#include "Audio/Jukebox.hpp"

void CMGT_PrototypeGame::Start()
{
	mainMenu_ = std::make_unique<MainMenu>(*this);
	AddScene(mainMenu_.get());
	activeScene_ = Scenes::MainMenu;
	
	eventHandler.Subscribe(sf::Event::KeyPressed, [](const sf::Event& event)
	{
		if (event.key.code == sf::Keyboard::T)
		{
			Jukebox::Play(Mode::Battle);
		}

		else if (event.key.code == sf::Keyboard::R)
		{
			Jukebox::Play(Mode::Idle);
		}

		if (event.key.code == sf::Keyboard::F)
		{
			Jukebox::currentMusic_.setPlayingOffset(Jukebox::currentMusic_.getDuration());
		}
	});
}

void CMGT_PrototypeGame::Update() 
{
	Jukebox::Update();
	TweenManager::Update();
	TimerManager::Update();
	DeleteScene(sceneToBeRemoved);
}

void CMGT_PrototypeGame::End() 
{
	
}

Scene* CMGT_PrototypeGame::SwapScene(const Scenes& scene) 
{
	switch (scene)
	{
		case Scenes::MainMenu:
			DeactivateScene(activeScene_);
			mainMenu_ = std::make_unique<MainMenu>(*this);
			AddScene(mainMenu_.get());
			activeScene_ = Scenes::MainMenu;
			return mainMenu_.get();
		
		case Scenes::Arena:
			DeactivateScene(activeScene_);
			arena_ = std::make_unique<Arena>(*this);
			AddScene(arena_.get());
			activeScene_ = Scenes::Arena;
			return arena_.get();
		
		case Scenes::Selection:
			DeactivateScene(activeScene_);
			selection_ = std::make_unique<Selection>(*this);
			AddScene(selection_.get());
			activeScene_ = Scenes::Selection;
			return selection_.get();
			
		case Scenes::None:
			DeactivateScene(activeScene_);
			return nullptr;
	};
	
	return nullptr;
}

void CMGT_PrototypeGame::DeactivateScene(const Scenes& scene) 
{
	TweenManager::ClearTweens();
	TimerManager::ClearTimers();

	switch (scene)
	{
		case Scenes::MainMenu:
			RemoveScene(mainMenu_.get());
			sceneToBeRemoved = Scenes::MainMenu;
			break;

		case Scenes::Arena:
			RemoveScene(arena_.get());
			sceneToBeRemoved = Scenes::Arena;
			break;

		case Scenes::Selection:
			RemoveScene(selection_.get());
			sceneToBeRemoved = Scenes::Selection;
			break;
			
		case Scenes::None:
			break;
	}
}

void CMGT_PrototypeGame::DeleteScene(const Scenes& scene) 
{
	switch (scene)
	{
		case Scenes::None:
			break;
		
		case Scenes::MainMenu:
			mainMenu_.reset();
			sceneToBeRemoved = Scenes::None;
			break;

		case Scenes::Arena:
			arena_.reset();
			sceneToBeRemoved = Scenes::None;
			break;

		case Scenes::Selection:
			selection_.reset();
			sceneToBeRemoved = Scenes::None;
			break;
	}
}