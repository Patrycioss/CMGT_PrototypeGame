#include "CMGT_PrototypeGame.hpp"
#include "Utility/InputHelper.hpp"



void CMGT_PrototypeGame::Start()
{
	mainMenu_ = std::make_unique<MainMenu>(*this);
	AddScene(mainMenu_.get());
	activeScene_ = Scenes::MainMenu;
}

void CMGT_PrototypeGame::Update() 
{
	DeleteScene(sceneToBeRemoved);
}

void CMGT_PrototypeGame::End() 
{
	
}

void CMGT_PrototypeGame::SwapScene(const Scenes& scene) 
{
	switch (scene)
	{
		case Scenes::MainMenu:
			DeactivateScene(activeScene_);
			mainMenu_ = std::make_unique<MainMenu>(*this);
			AddScene(mainMenu_.get());
			activeScene_ = Scenes::MainMenu;
			break;
		
		case Scenes::Arena:
			DeactivateScene(activeScene_);
			arena_ = std::make_unique<Arena>(*this);
			AddScene(arena_.get());
			activeScene_ = Scenes::Arena;
			break;
		
		case Scenes::Selection:
			DeactivateScene(activeScene_);
			selection_ = std::make_unique<Selection>(*this);
			AddScene(selection_.get());
			activeScene_ = Scenes::Selection;
			break;
			
		case Scenes::None:
			DeactivateScene(activeScene_);
			break;
	}
}

void CMGT_PrototypeGame::DeactivateScene(const Scenes& scene) 
{
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

//eventHandler.Subscribe(sf::Event::KeyPressed, [=](sf::Event event)
//{
//if (event.key.code == sf::Keyboard::V)
//{
//animationTest->Visible(!animationTest->Visible());
//}
//else if (event.key.code == sf::Keyboard::M)
//{
//animationTest->MirrorVert(!animationTest->vertMirrored());
//}
//else if (event.key.code == sf::Keyboard::C)
//{
//testSprite->MirrorHor(!testSprite->horMirrored());
//}
//else if (event.key.code == sf::Keyboard::F)
//{
//testSprite->MirrorVert(!testSprite->vertMirrored());
//}
//else if (event.key.code == sf::Keyboard::B)
//{
//main_menu.MirrorHor(!main_menu.horMirrored());
//}
//else if (event.key.code == sf::Keyboard::G)
//{
//main_menu.Mirror(!main_menu.horMirrored(),!main_menu.vertMirrored());
//}
//else if (event.key.code == sf::Keyboard::Add)
//{
//testSprite->SetScale(0.5f,0.5f);
//}
//else if (event.key.code == sf::Keyboard::Subtract)
//{
//testSprite->SetScale(1,1);
//}
//
//});




