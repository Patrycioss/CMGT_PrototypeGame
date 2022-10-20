#include "CMGT_PrototypeGame.hpp"
#include "Utility/InputHelper.hpp"

void CMGT_PrototypeGame::Start()
{
	
	testSprite = new TestSprite(sf::Vector2f(0,0));
	
	animationTest = new AnimationTest(sf::Vector2f(0,0));
	animationTest2 = new AnimationTest(sf::Vector2f(100,100));


	main_menu.AddChild(testSprite);
	testSprite->AddChild(animationTest);
	animationTest->AddChild(animationTest2);

	AddScene(main_menu.name(),&main_menu);
	
	eventHandler.Subscribe(sf::Event::KeyPressed, [=](sf::Event event)
	{
		if (event.key.code == sf::Keyboard::V)
		{
			animationTest->Visible(!animationTest->Visible());
		}
		else if (event.key.code == sf::Keyboard::M)
		{
			animationTest->MirrorVert(!animationTest->vertMirrored());
		}
		else if (event.key.code == sf::Keyboard::C)
		{
			testSprite->MirrorHor(!testSprite->horMirrored());
		}
		else if (event.key.code == sf::Keyboard::F)
		{
			testSprite->MirrorVert(!testSprite->vertMirrored());
		}
		else if (event.key.code == sf::Keyboard::B)
		{
			main_menu.MirrorHor(!main_menu.horMirrored());
		}
		else if (event.key.code == sf::Keyboard::G)
		{
			main_menu.Mirror(!main_menu.horMirrored(),!main_menu.vertMirrored());
		}
	});
}

void CMGT_PrototypeGame::Update() 
{
	animationTest->Animate();
	animationTest2->Animate();
	testSprite->Move(InputHelper::get_arrowKeys_direction());
	animationTest->Move(InputHelper::get_wasd_direction());
}

void CMGT_PrototypeGame::End() 
{
	delete testSprite;
	delete animationTest;
}   




